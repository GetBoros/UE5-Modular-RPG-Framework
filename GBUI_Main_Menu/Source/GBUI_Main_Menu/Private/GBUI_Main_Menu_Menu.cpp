//------------------------------------------------------------------------------------------------------------
#include <GBUI_Main_Menu_Menu.h>
#include <GBUI_Main_Menu_Button.h>
#include <GBUIC_User_Widget.h>
#include <GBUIC_Widget_Controller_Menu.h>

#include <GameFramework/PlayerController.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu
void UGBUI_Main_Menu::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::NativeConstruct()
{
    APlayerController *player_controller;
	FInputModeUIOnly input_mode_data;

	Super::NativeConstruct();

	input_mode_data.SetWidgetToFocus(Button_New_Game->TakeWidget() );
	input_mode_data.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	player_controller = GetOwningPlayer();
	player_controller->SetInputMode(input_mode_data);

	Init();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Init()
{
    UGBUI_Main_Menu_Button *menu_button_new_game = Cast<UGBUI_Main_Menu_Button>(Button_New_Game);

	if (menu_button_new_game == 0)
		return;

	menu_button_new_game->On_Button_Pressed.AddUniqueDynamic(this, &UGBUI_Main_Menu::Handle_Button_New_Game);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Handle_Button_New_Game()
{
	UGBUIC_Widget_Controller_Menu *menu_widget_controller = Cast<UGBUIC_Widget_Controller_Menu>(Widget_Controller);
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("UI.Menu.NewGame") );

	menu_widget_controller->Set_Menu_State(tag);
}
//------------------------------------------------------------------------------------------------------------
