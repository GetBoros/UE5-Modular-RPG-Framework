//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <GAS/GBG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Widget_Controller
void UGBUI_Widget_Controller::On_Stamina_Changed_Callback(const FOnAttributeChangeData& data)
{
    On_Stamina_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Set_Widget_Controller_Params(const FController_Widget_Params &params)
{
    Ability_System_Component = params.Ability_System_Component;
    Attribute_Set = Cast<UGBG_Attribute_Set>(params.Attribute_Set);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    if (Ability_System_Component == 0 || Attribute_Set == 0)
        return;

    On_Stamina_Changed.Broadcast(Attribute_Set->Get_Stamina() );  // Send initial value. Receive current and send to our UI

    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetStaminaAttribute() ).AddUObject(this, &UGBUI_Widget_Controller::On_Stamina_Changed_Callback);  // Call our func when value chang
}
//------------------------------------------------------------------------------------------------------------
