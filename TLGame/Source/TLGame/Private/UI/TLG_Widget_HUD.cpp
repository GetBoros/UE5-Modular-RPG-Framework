//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Controller.h>
#include <UI/TLG_Widget_Floating_Text.h>
#include <System/TLG_Player_State.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
#include <Components/Image.h>
#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    ensureMsgf(Floating_Text_Class, TEXT("Floating Text Class not setting up") );
    ensureMsgf(TLG_Widget_Controller_Class, TEXT("Is Empty") );

    Init_Widget_Controller();

    Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Show_Node(const FDialogue_Node &node_data)
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Visible);
    TLG_Widget_Dialogue->Setup_Dialogue_Node(node_data);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Hide() const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Hidden);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Background_Texture(UTexture2D *image_background_texture) const
{
    Image_Background->SetBrushFromTexture(image_background_texture);
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
    
	// 2.0. Create and initialize tlg widget controller
    TLG_Widget_Controller = NewObject<UTLG_Widget_Controller>(this, TLG_Widget_Controller_Class);
    TLG_Widget_Controller->Init(controller_widget_params);
    
    TLG_Widget_Controller->On_Changed_Sanity.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Sanity);
    TLG_Widget_Controller->On_Changed_Dominance.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Dominance);
    
    TLG_Widget_Controller->Bind_Callbacks_To_Dependencies();
    TLG_Widget_Controller->Broadcast_Initial_Values();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Spawn_Floating_Text(float delta, const FText &name_text)
{
    UUserWidget *widget;
    UTLG_Widget_Floating_Text *float_widget;

    if (VB_Events == 0 || Floating_Text_Class == 0)
        return;

    widget = CreateWidget<UUserWidget>(this, Floating_Text_Class);
    float_widget = Cast<UTLG_Widget_Floating_Text>(widget);
    if (float_widget == 0)
        return;

    FString sign = (delta > 0) ? TEXT("+") : TEXT("");
    FText final_text = FText::FromString(FString::Printf(TEXT("%s%d %s"), *sign, FMath::RoundToInt(delta), *name_text.ToString() ) );
    FLinearColor color = (delta > 0) ? FLinearColor::Green : FLinearColor::Red;  // !!! TEMP can change if dominance to swap color
    
    float_widget->Setup_Visuals(final_text, color);
    
    VB_Events->AddChild(float_widget);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Sanity(float new_value, float delta)
{
    On_Updated_Sanity(new_value, 100.0f);

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Floating_Text(delta, FText::FromString("Sanity") );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Changed_Callback_Dominance(float new_value, float delta)
{
    On_Updated_Dominance(new_value);

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Floating_Text(delta, FText::FromString("Dominance") );
}
//------------------------------------------------------------------------------------------------------------
