//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Text_Floating.h>
#include <UI/TLG_Widget_Button.h>
#include <UI/TLG_Widget_Portrait.h>
#include <UI/TLG_Widget_Controller.h>
#include <Data/TLG_Data_Location.h>

#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    Super::NativeConstruct();

    if (ensureMsgf(TLG_Widget_Button_Action_Class, TEXT("Is Empty") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Button_Navigation_Class, TEXT("Is Empty") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Text_Floating_Class, TEXT("Floating Text Class not setting up") ) != true)
        return;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Node_Show(const FDialogue_Node &node_data)
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Visible);
    TLG_Widget_Dialogue->Setup_Dialogue_Node(node_data);
    TLG_Widget_Portrait_Enemy->Set_Image_Portrait_Visibility(true);
    VB_Button_Navigation->SetVisibility(ESlateVisibility::Collapsed);
    VB_Button_Actions->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Hide() const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Hidden);
    TLG_Widget_Portrait_Enemy->Set_Image_Portrait_Visibility(false);
    VB_Button_Navigation->SetVisibility(ESlateVisibility::Visible);
    VB_Button_Actions->SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Texture_Background(UTexture2D *image_background_texture)
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
            tlg_widget_button_action->Set_Widget_Controller(GBUIC_Widget_Controller);
            tlg_widget_button_action->Init(location_action);
            
            VB_Button_Actions->AddChild(tlg_widget_button_action);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Widget_Controller()
{
    UTLG_Widget_Controller *tlg_widget_controller;

    if (GBUIC_Widget_Controller == 0)
        return;
    
    tlg_widget_controller = Cast<UTLG_Widget_Controller>(GBUIC_Widget_Controller);
    
    tlg_widget_controller->On_Changed_Sanity.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Sanity);
    tlg_widget_controller->On_Changed_Dominance.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Dominance);
    tlg_widget_controller->On_Changed_Time_Game.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Time_Game);
    tlg_widget_controller->On_Changed_Day.AddDynamic(this, &UTLG_Widget_HUD::On_Changed_Callback_Day);

    tlg_widget_controller->On_Game_Over.AddUObject(this, &UTLG_Widget_HUD::On_Game_Over);
    tlg_widget_controller->On_Game_Resumed.AddUObject(this, &UTLG_Widget_HUD::On_Game_Resumed);
    tlg_widget_controller->On_Game_Menu_Paused.AddUObject(this, &UTLG_Widget_HUD::On_Game_Menu_Paused);
    tlg_widget_controller->On_Game_Demo_Completed.AddUObject(this, &UTLG_Widget_HUD::On_Game_Menu_Paused);


    tlg_widget_controller->Bind_Callbacks_To_Dependencies();
    tlg_widget_controller->Broadcast_Initial_Values();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Updated_Temp_Implementation(float sanity_curr, float sanity_max)
{
    // !!! TEMP
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Spawn_Text_Floating(float delta, const FText &name_text)
{
    UTLG_Widget_Text_Floating *tlg_widget_text_floating;

    tlg_widget_text_floating = CreateWidget<UTLG_Widget_Text_Floating>(this, TLG_Widget_Text_Floating_Class);
    if (tlg_widget_text_floating == 0)
        return;

    FString string_sign = (delta > 0) ? TEXT("+") : TEXT("");
    FText text_final = FText::FromString(FString::Printf(TEXT("%s%d %s"), *string_sign, FMath::RoundToInt(delta), *name_text.ToString() ) );
    FLinearColor linear_color = (delta > 0) ? FLinearColor::Green : FLinearColor::Red;  // !!! TEMP can change if dominance to swap color
    
    tlg_widget_text_floating->Setup_Visuals(text_final, linear_color);
    
    VB_Text_Floating_Events->AddChild(tlg_widget_text_floating);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Game_Over()
{
    SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Game_Resumed()
{
    SetVisibility(ESlateVisibility::Visible);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Game_Menu_Paused()
{
    SetVisibility(ESlateVisibility::Hidden);
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
