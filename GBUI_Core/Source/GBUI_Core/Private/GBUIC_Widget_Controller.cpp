//------------------------------------------------------------------------------------------------------------
#include <GBUIC_Widget_Controller.h>

#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UGBUIC_Widget_Controller
void UGBUIC_Widget_Controller::Init(const FController_Widget_Params& params)
{
    Player_Controller = params.Player_Controller;
    Player_State = params.Player_State;
    Ability_System_Component = params.Ability_System_Component;
    Attribute_Set = params.Attribute_Set;
    Attribute_Info = params.Attribute_Info;
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::Broadcast_Initial_Values()
{

}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::Bind_Callbacks_To_Dependencies()
{

}
//------------------------------------------------------------------------------------------------------------
