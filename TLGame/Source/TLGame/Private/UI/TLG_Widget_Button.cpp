//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Button.h>
#include <UI/TLG_Widget_Controller.h>
#include <UI/TLG_Widget_Tooltip.h>

#include <Components/TLG_Component_Navigation.h>
#include <Libraries/GBC_Library.h>

#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button
void UTLG_Widget_Button::NativeDestruct()
{
    Super::NativeDestruct();

    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button::Handle_Click_Internal);
    Button_Click->OnHovered.RemoveDynamic(this, &UTLG_Widget_Button::Handle_Hover_Internal);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::NativeConstruct()
{
    Super::NativeConstruct();

    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button::Handle_Click_Internal);
    Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button::Handle_Click_Internal);

    Button_Click->OnHovered.RemoveDynamic(this, &UTLG_Widget_Button::Handle_Hover_Internal);
    Button_Click->OnHovered.AddDynamic(this, &UTLG_Widget_Button::Handle_Hover_Internal);

    if (ensureMsgf(TLG_Widget_Tooltip_Class, TEXT("Hello World!") ) != true)
        return;

    if (TLG_Widget_Tooltip == 0)
    {
        TLG_Widget_Tooltip = CreateWidget<UTLG_Widget_Tooltip>(GetOwningPlayer(), TLG_Widget_Tooltip_Class);
        TLG_Widget_Tooltip->Update_TB_Description(Text_Tooltip_Description);
    }

    if (TLG_Widget_Tooltip != 0)
        SetToolTip(TLG_Widget_Tooltip);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::On_Widget_Controller_Set_Implementation()
{
	TLG_Widget_Controller = Cast<UTLG_Widget_Controller>(GBUIC_Widget_Controller);  // Cast GBUI to TLG Controller must be first after use say child class from parent class

    Super::On_Widget_Controller_Set_Implementation();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Handle_Click()
{
    if (Gameplay_Tag.IsValid() == true)  // if tag is not empty try activate ability if object have this ability
        TLG_Widget_Controller->Request_Ability_Activation(Gameplay_Tag);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Set_Button_Text(const FText &text_button) const
{
    if (text_button.IsEmpty() == true)
        TB_Button->SetText(FText::FromString(TEXT("Empty No Name in UTLG_Data_Location DA") ) );
    else
        TB_Button->SetText(text_button);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Set_Button_Enabled(const bool is_enabled)
{
    Button_Click->SetIsEnabled(is_enabled);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Handle_Click_Internal()
{
    if (Sound_Click != 0)
        UGameplayStatics::PlaySound2D(this, Sound_Click);

    Handle_Click();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Handle_Hover_Internal()
{
    // !!! TEMP Add tooltips? show descriptions

    if (Sound_Hover != 0)
        UGameplayStatics::PlaySound2D(this, Sound_Hover);
}
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Action
void UTLG_Widget_Button_Action::NativeDestruct()
{
    Super::NativeDestruct();

    TLG_Widget_Controller->On_Player_Attribute_Changed.RemoveAll(this);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::NativeConstruct()
{
    Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::On_Widget_Controller_Set_Implementation()
{
    Super::On_Widget_Controller_Set_Implementation();  // Cast GBUI to TLG Controller must be first after use TLG

    TLG_Widget_Controller->On_Player_Attribute_Changed.AddUObject(this, &UTLG_Widget_Button_Action::Refresh_Button_State);  // !!! TEMP change to not dynamic
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::Handle_Click()
{
    APlayerController *player_controller;
    ITLG_Interaction_Interface *interaction_interface;

    Super::Handle_Click();

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    interaction_interface = Cast<ITLG_Interaction_Interface>(player_controller);
    if (interaction_interface != 0)
        interaction_interface->Location_Action(TLG_Location_Action);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::Init(const FTLG_Location_Action &tlg_location_action)
{
    bool is_button_enabled;
    const int32 time_cost_minutes = tlg_location_action.Time_Cost_Minutes;
    const FText text_button = tlg_location_action.Text_Button;
    const FText text_format_pattern = FText::FromString("{0} ({1})");
    const FText text_time = UGBC_Library::Format_Time_From_Minutes(time_cost_minutes);
    const FText text_final = FText::Format(text_format_pattern, text_button, text_time);

    // 1.0. Init
    TLG_Location_Action = tlg_location_action;
    is_button_enabled = TLG_Widget_Controller->Check_Action_Requirements(TLG_Location_Action.Action_Requirement);
    Gameplay_Tag = tlg_location_action.Gameplay_Tag;

	// 1.1. Set Text in Button
    if (text_button.IsEmpty() == true)
        Set_Button_Text(FText::FromString(FString(TEXT("Empty No Name in UTLG_Data_Location DA") ) ) );
    else
        Set_Button_Text(text_final);

    // 1.1.a. Set Text in Button Tooltip Descriptions
    Text_Tooltip_Description = tlg_location_action.Text_Button_Tooltip_Description;

	// 1.2. Enable or Disable Button
	Set_Button_Enabled(is_button_enabled);

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::Refresh_Button_State()
{
    const bool is_button_available = TLG_Widget_Controller->Check_Action_Requirements(TLG_Location_Action.Action_Requirement);

    Set_Button_Enabled(is_button_available);
}
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Navigation
void UTLG_Widget_Button_Navigation::Handle_Click()
{
    APlayerController *player_controller;
    UTLG_Component_Navigation *tlg_component_navigation;

    Super::Handle_Click();

    if (Target_Location == 0)
        return;

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    tlg_component_navigation = player_controller->FindComponentByClass<UTLG_Component_Navigation>();
	tlg_component_navigation->Set_Location_Current(Target_Location);
    tlg_component_navigation->Location_Enter();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Navigation::Init(const FTLG_Location_Exit &exit_data)
{
    const FText text_button = exit_data.Text_Button;

    Target_Location = exit_data.TLG_Data_Location_Target;
    
    if (text_button.IsEmpty() == true)
        Set_Button_Text(FText::FromString(FString(TEXT("Empty No Name in UTLG_Data_Location DA") ) ) );
    else
        Set_Button_Text(text_button);
}
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Flow
void UTLG_Widget_Button_Flow::Handle_Click()
{
    APlayerController *player_controller;
    ITLG_Interaction_Interface *interaction_interface;

    Super::Handle_Click();

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    interaction_interface = Cast<ITLG_Interaction_Interface>(player_controller);
    if (interaction_interface != 0)
        interaction_interface->Request_Menu_Main_Pause(TLG_Game_Flow_Option);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Flow::Init(const ETLG_Game_Flow_Option tlg_game_flow_option, const FText &text_button)
{
    TLG_Game_Flow_Option = tlg_game_flow_option;
    Set_Button_Text(text_button);
}
//------------------------------------------------------------------------------------------------------------

