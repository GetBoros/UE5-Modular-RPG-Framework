//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------





// UGBUI_Widget_Controller
UGBUI_Widget_Controller::UGBUI_Widget_Controller()
{
    Stamina_Tag = FGameplayTag::RequestGameplayTag(FName("Attributes.Vitality.Stamina") );
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::On_Stamina_Changed_Callback(const FOnAttributeChangeData& data)
{
    On_Stamina_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Set_Widget_Controller_Params(const FController_Widget_Params &params)
{
    Ability_System_Component = params.Ability_System_Component;
    Attribute_Info = params.Attribute_Info_Asset;
    Attribute_Info_Stamina = Attribute_Info->Find_Attribute_Info_By_Tag(Stamina_Tag);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    if (Ability_System_Component == 0 || Attribute_Info == 0)
        return;

    if (Attribute_Info_Stamina.Attribute_To_Bind.IsValid() == true)
        Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Info_Stamina.Attribute_To_Bind).AddUObject(this, &UGBUI_Widget_Controller::On_Stamina_Changed_Callback);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Broadcast_Initial_Values()
{
    if (Ability_System_Component == 0 || Attribute_Info == 0)
        return;

    if (Attribute_Info_Stamina.Attribute_To_Bind.IsValid() )
    {
        float val = Ability_System_Component->GetNumericAttribute(Attribute_Info_Stamina.Attribute_To_Bind);

        On_Stamina_Changed.Broadcast(val);
    }
}
//------------------------------------------------------------------------------------------------------------
