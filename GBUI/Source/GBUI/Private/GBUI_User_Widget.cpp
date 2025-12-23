//------------------------------------------------------------------------------------------------------------
#include <GBUI_User_Widget.h>
#include <GBUI_Widget_Controller.h>
//------------------------------------------------------------------------------------------------------------



// UGBUI_User_Widget
void UGBUI_User_Widget::Set_Widget_Controller(UObject *in_controller)
{
    Widget_Controller = Cast<UGBUI_Widget_Controller>(in_controller);

    On_Widget_Controller_Set();
}
//------------------------------------------------------------------------------------------------------------