//------------------------------------------------------------------------------------------------------------
#include <GBUIC_Widget_Controller.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------





// UGBUIC_Widget_Controller
UGBUIC_Widget_Controller::UGBUIC_Widget_Controller()
{
    Stamina_Tag = FGameplayTag::RequestGameplayTag(FName("Attributes.Vitality.Stamina") );
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::Init(const FController_Widget_Params &params)
{
    Ability_System_Component = params.Ability_System_Component;
    Attribute_Info = params.Attribute_Info_Asset;
    Attribute_Info_Stamina = Attribute_Info->Find_Attribute_Info_By_Tag(Stamina_Tag);

    Bind_Callbacks_To_Dependencies();
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::Broadcast_Initial_Values()
{
    if (Ability_System_Component == 0 || Attribute_Info == 0)
        return;

    if (Attribute_Info_Stamina.Attribute_To_Bind.IsValid() )
        On_Stamina_Changed.Broadcast(Ability_System_Component->GetNumericAttribute(Attribute_Info_Stamina.Attribute_To_Bind) );
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    if (Ability_System_Component == 0 || Attribute_Info == 0)
        return;

    if (Attribute_Info_Stamina.Attribute_To_Bind.IsValid() == true)
        Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Info_Stamina.Attribute_To_Bind).AddUObject(this, &UGBUIC_Widget_Controller::On_Stamina_Changed_Callback);
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller::On_Stamina_Changed_Callback(const FOnAttributeChangeData &data)
{
    On_Stamina_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------




// UGBUIC_Widget_Controller_Temp
void UGBUIC_Widget_Controller_Temp::Init(const FController_Widget_Params_Temp& params)
{
    Player_Controller = params.Player_Controller;
    Player_State = params.Player_State;
    Ability_System_Component = params.Ability_System_Component;
    Attribute_Set = params.Attribute_Set;
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller_Temp::Broadcast_Initial_Values()
{

}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Widget_Controller_Temp::Bind_Callbacks_To_Dependencies()
{

}
//------------------------------------------------------------------------------------------------------------
