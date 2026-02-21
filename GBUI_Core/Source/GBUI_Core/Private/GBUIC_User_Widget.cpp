//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <GBUIC_Widget_Controller.h>
//------------------------------------------------------------------------------------------------------------



// UGBUIC_User_Widget
void UGBUIC_User_Widget::On_Widget_Controller_Set_Implementation()
{
    
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_User_Widget::Set_Widget_Controller(UGBUIC_Widget_Controller *gbuic_widget_controller)
{
    GBUIC_Widget_Controller = gbuic_widget_controller;

    On_Widget_Controller_Set();
}
//------------------------------------------------------------------------------------------------------------
