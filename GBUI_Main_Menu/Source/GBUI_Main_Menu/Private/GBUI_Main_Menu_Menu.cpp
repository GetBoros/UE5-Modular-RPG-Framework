//------------------------------------------------------------------------------------------------------------
#include <GBUI_Main_Menu_Menu.h>
#include <GBUI_Main_Menu_Button.h>
#include <GBUIC_User_Widget.h>
#include <GBUIC_Widget_Controller_Menu.h>

#include <GameFramework/PlayerController.h>
//------------------------------------------------------------------------------------------------------------
UE_DEFINE_GAMEPLAY_TAG(TAG_MENU_NEW_GAME, "UI.Menu.NewGame");
UE_DEFINE_GAMEPLAY_TAG(TAG_MENU_LOAD, "UI.Menu.Load");
UE_DEFINE_GAMEPLAY_TAG(TAG_MENU_SETTINGS, "UI.Menu.Settings");
UE_DEFINE_GAMEPLAY_TAG(TAG_MENU_EXIT, "UI.Menu.Exit");
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
UGBUIC_Widget_Controller_Menu* UGBUI_Main_Menu::Get_Menu_Controller()
{
	return Cast<UGBUIC_Widget_Controller_Menu>(GBUIC_Widget_Controller);
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
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("UI.Menu.NewGame") );

	Get_Menu_Controller()->Set_Menu_State(tag);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Handle_Button_Load()
{
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("UI.Menu.Load") );

	Get_Menu_Controller()->Set_Menu_State(tag);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Handle_Button_Settings()
{
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("UI.Menu.Settings") );

	Get_Menu_Controller()->Set_Menu_State(tag);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Handle_Button_Exit()
{
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("UI.Menu.Exit") );

	Get_Menu_Controller()->Set_Menu_State(tag);
}
//------------------------------------------------------------------------------------------------------------
