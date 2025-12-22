//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Widget_Controller
void UGBUI_Widget_Controller::Set_Widget_Controller_Params(APlayerController *pc, APlayerState *ps, UAbilitySystemComponent *asc, UAttributeSet *as)
{
    Player_Controller = pc;
    Player_State = ps;
    Ability_System_Component = asc;
    Attribute_Set = as;
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Broadcast_Initial_Values()
{
    // This function is meant to be overridden in child classes.
    // For example, HUDWidgetController will broadcast initial Health, Stamina etc.
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    // This function is meant to be overridden in child classes.
    // It will subscribe to attribute change delegates.
}
//------------------------------------------------------------------------------------------------------------