//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <Types/GBC_Attribute_Info.h>
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
    Attribute_Set = params.Attribute_Set;
    Attribute_Info = params.Attribute_Info_Asset;
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    if (Ability_System_Component == 0 || Attribute_Set == 0)
        return;

    FGameplayTag stamina_tag = FGameplayTag::RequestGameplayTag(FName("Attributes.Vitality.Stamina") );
    FGBC_Attribute_Info_Item info = Attribute_Info->Find_Attribute_Info_By_Tag(stamina_tag);

    if (info.Attribute_To_Bind.IsValid() == true)
        Ability_System_Component->GetGameplayAttributeValueChangeDelegate(info.Attribute_To_Bind).AddUObject(this, &UGBUI_Widget_Controller::On_Stamina_Changed_Callback);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Widget_Controller::Broadcast_Initial_Values()
{
    if (Ability_System_Component == 0 || Attribute_Info == 0)
        return;

    const FGameplayTag stamina_tag = FGameplayTag::RequestGameplayTag(FName("Attributes.Vitality.Stamina") );
    FGBC_Attribute_Info_Item info = Attribute_Info->Find_Attribute_Info_By_Tag(stamina_tag);

    if (info.Attribute_To_Bind.IsValid() )
    {
        float val = Ability_System_Component->GetNumericAttribute(info.Attribute_To_Bind);

        On_Stamina_Changed.Broadcast(val);
    }
}
//------------------------------------------------------------------------------------------------------------
