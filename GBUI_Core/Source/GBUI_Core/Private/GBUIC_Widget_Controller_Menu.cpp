//------------------------------------------------------------------------------------------------------------
#include "GBUIC_Widget_Controller_Menu.h"
//------------------------------------------------------------------------------------------------------------




// UGBUIC_Widget_Controller_Menu
void UGBUIC_Widget_Controller_Menu::Set_Menu_State(FGameplayTag new_state)
{
    if (Current_State == new_state)
        return;

    Current_State = new_state;

    On_Menu_State_Changed.Broadcast(Current_State);  // Сообщаем всем (Виджету), что состояние изменилось
}
//------------------------------------------------------------------------------------------------------------
