//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Controller.h>
#include <UI/TLG_Widget_Text_Floating.h>
#include "UI/TLG_Widget_Button.h"
#include <UI/TLG_Widget_Portrait.h>
#include <System/TLG_Player_State.h>
#include <Abilities/TLG_Attribute_Set.h>
#include <Data/TLG_Data_Location.h>

#include <AbilitySystemComponent.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    Super::NativeConstruct();

    if (ensureMsgf(TLG_Widget_Text_Floating, TEXT("Floating Text Class not setting up") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Controller_Class, TEXT("Is Empty") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Button_Action_Class, TEXT("Is Empty") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Button_Navigation_Class, TEXT("Is Empty") ) != true)
        return;
    
    Init_Widget_Controller();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Node_Show(const FDialogue_Node &node_data)
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Visible);
    TLG_Widget_Dialogue->Setup_Dialogue_Node(node_data);
    TLG_Widget_Portrait_Enemy->Set_Image_Portrait_Visibility(true);
    VB_Button_Navigation->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Hide() const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Hidden);
    TLG_Widget_Portrait_Enemy->Set_Image_Portrait_Visibility(false);
    VB_Button_Navigation->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Texture_Background(UTexture2D *image_background_texture) const
{
    Image_Background->SetBrushFromTexture(image_background_texture);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Texture_Portrait(UTexture2D *image_portrait_texture)
{
    TLG_Widget_Portrait_Enemy->Set_Image_Portrait_Texture(image_portrait_texture);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Update_Buttons_Navigation(const TArray<FTLG_Location_Exit> &tlg_location_exits)
{
    UTLG_Widget_Button_Navigation *tlg_widget_button_navigation;
    
    VB_Button_Navigation->ClearChildren();

    for (const FTLG_Location_Exit &location_exit: tlg_location_exits)
    {
        tlg_widget_button_navigation = CreateWidget<UTLG_Widget_Button_Navigation>(this, TLG_Widget_Button_Navigation_Class);
        if (tlg_widget_button_navigation != 0)
        {
            tlg_widget_button_navigation->Init(location_exit);

            VB_Button_Navigation->AddChild(tlg_widget_button_navigation);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Update_Buttons_Actions(const TArray<FTLG_Location_Action> &tlg_location_action)
{
    UTLG_Widget_Button_Action *tlg_widget_button_action;

    VB_Button_Actions->ClearChildren();

    for (const FTLG_Location_Action &location_action : tlg_location_action)
    {
        tlg_widget_button_action = CreateWidget<UTLG_Widget_Button_Action>(this, TLG_Widget_Button_Action_Class);
        if (tlg_widget_button_action != 0)
        {
            tlg_widget_button_action->Init(location_action);

            VB_Button_Actions->AddChild(tlg_widget_button_action);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Game_Over()
{
    Text_Game_Over->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Updated_Temp_Implementation(float sanity_curr, float sanity_max)
{
    // !!! TEMP
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Init_Widget_Controller()
{
    APlayerController *player_controller;
    ATLG_Player_State *tlg_player_state;
    UAbilitySystemComponent *ability_system_component;
    UTLG_Attribute_Set *tlg_attribute_set;
    FController_Widget_Params controller_widget_params;

	if (TLG_Widget_Controller != 0)  // If already initialized
        return;

	// 1.0. Initialize reguired references
    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    tlg_player_state = player_controller->GetPlayerState<ATLG_Player_State>();
    if (tlg_player_state == 0)
        return;

    ability_system_component = tlg_player_state->GetAbilitySystemComponent();
    tlg_attribute_set = tlg_player_state->Get_Attribute_Set();
    if (ability_system_component == 0 || tlg_attribute_set == 0)
        return;

    controller_widget_params.Player_Controller = player_controller;
    controller_widget_params.Player_State = tlg_player_state;
    controller_widget_params.Ability_System_Component = ability_system_component;
    controller_widget_params.Attribute_Set = tlg_attribute_set;
    controller_widget_params.Attribute_Info = GBC_Attribute_Info;
    controller_widget_params.Game_State_Base = GetWorld()->GetGameState();
    
	// 2.0. Create and initialize tlg widget controller
    TLG_Widget_Controller = NewObject<UTLG_Widget_Controller>(this, TLG_Widget_Controller_Class);
    TLG_Widget_Controller->Init(controller_widget_params);
    
    TLG_Widget_Controller->On_Changed_Sanity.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Sanity);
    TLG_Widget_Controller->On_Changed_Dominance.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Dominance);
    TLG_Widget_Controller->On_Changed_Time_Game.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Time_Game);
    TLG_Widget_Controller->On_Changed_Day.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Day);

    TLG_Widget_Controller->Bind_Callbacks_To_Dependencies();
    TLG_Widget_Controller->Broadcast_Initial_Values();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Spawn_Text_Floating(float delta, const FText &name_text)
{
    UTLG_Widget_Text_Floating *tlg_widget_text_floating;

    tlg_widget_text_floating = CreateWidget<UTLG_Widget_Text_Floating>(this, TLG_Widget_Text_Floating);
    if (tlg_widget_text_floating == 0)
        return;

    FString string_sign = (delta > 0) ? TEXT("+") : TEXT("");
    FText text_final = FText::FromString(FString::Printf(TEXT("%s%d %s"), *string_sign, FMath::RoundToInt(delta), *name_text.ToString() ) );
    FLinearColor linear_color = (delta > 0) ? FLinearColor::Green : FLinearColor::Red;  // !!! TEMP can change if dominance to swap color
    
    tlg_widget_text_floating->Setup_Visuals(text_final, linear_color);
    
    VB_Text_Floating_Events->AddChild(tlg_widget_text_floating);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Sanity(float new_value, float delta)
{
    On_Updated_Sanity(new_value, 100.0f);

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Text_Floating(delta, FText::FromString("Sanity") );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Dominance(float new_value, float delta)
{
    On_Updated_Dominance(new_value);

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Text_Floating(delta, FText::FromString("Dominance") );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Day(int32 current_day)
{
    FString day_str = FString::Printf(TEXT("Day %d"), current_day);

    Text_Day_Counter->SetText(FText::FromString(day_str) );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Time_Game(int32 hours, int32 minutes)
{
    FString time_str = FString::Printf(TEXT("%02d:%02d"), hours, minutes);

    Text_Clock->SetText(FText::FromString(time_str) );
}
//------------------------------------------------------------------------------------------------------------
