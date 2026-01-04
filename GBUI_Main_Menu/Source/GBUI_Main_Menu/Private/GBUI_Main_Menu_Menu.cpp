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
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Temp()
{
    UGBUI_Main_Menu_Button *test = Cast<UGBUI_Main_Menu_Button>(Button_New_Game);

	if (test != 0)
		return;

	test->On_Button_Pressed.AddDynamic(this, &UGBUI_Main_Menu::Test);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::Test()
{

}
//------------------------------------------------------------------------------------------------------------
