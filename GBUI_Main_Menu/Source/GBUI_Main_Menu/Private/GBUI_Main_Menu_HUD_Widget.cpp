//------------------------------------------------------------------------------------------------------------
#include <GBUI_Main_Menu_HUD_Widget.h>
#include <GBUI_Main_Menu_Menu.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu_HUD_Widget
void UGBUI_Main_Menu_HUD_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();

}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_HUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	Menu_Main->Set_Widget_Controller(GBUIC_Widget_Controller);
}
//------------------------------------------------------------------------------------------------------------
