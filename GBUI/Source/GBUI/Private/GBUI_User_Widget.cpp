//------------------------------------------------------------------------------------------------------------
#include <GBUI_User_Widget.h>
#include <GBUI_Widget_Controller.h>
//------------------------------------------------------------------------------------------------------------



// UGBUI_User_Widget
void UGBUI_User_Widget::Set_Widget_Controller(UGBUI_Widget_Controller *widget_controller)
{
    Widget_Controller = widget_controller;

    On_Widget_Controller_Set();
}
//------------------------------------------------------------------------------------------------------------