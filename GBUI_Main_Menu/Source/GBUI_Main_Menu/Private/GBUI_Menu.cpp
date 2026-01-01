//------------------------------------------------------------------------------------------------------------
#include <GBUI_Menu.h>
#include <GBUI_Main_Menu_Button.h>
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

    if (VB_Button_Container == 0 || Button_Class == 0)
        return;

    VB_Button_Container->ClearChildren();  // !!! TEMP

    for (const FGBUI_Menu_Button_Info &info : Buttons_Config)
    {
        UGBUI_Main_Menu_Button *new_button = CreateWidget<UGBUI_Main_Menu_Button>(this, Button_Class);

        new_button->Button_Text = info.Button_Text;

        VB_Button_Container->AddChildToVerticalBox(new_button);
    }
}
//------------------------------------------------------------------------------------------------------------
