//------------------------------------------------------------------------------------------------------------
#include <GBUI_Menu.h>
#include <GBUI_Main_Menu_Button.h>
#include <GBUI_User_Widget.h>

#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu
void UGBUI_Main_Menu::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct Called! Object: %p, Name: %s"), this, *GetName());
	//FDebug::DumpStackTraceToLog();

    if (VB_Button_Container == 0)
        return;

    VB_Button_Container->ClearChildren();  // !!! TEMP
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
