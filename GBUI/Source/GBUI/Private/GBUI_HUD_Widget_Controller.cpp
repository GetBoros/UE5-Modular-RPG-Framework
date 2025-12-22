//------------------------------------------------------------------------------------------------------------
#include <GBUI_HUD_Widget_Controller.h>
#include <AbilitySystemComponent.h>
#include <GAS/GBG_Attribute_Set.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_HUD_Widget_Controller
void UGBUI_HUD_Widget_Controller::Broadcast_Initial_Values()
{
    Super::Broadcast_Initial_Values();

    if (Attribute_Set == 0)
        return;

    // We need our specific Attribute Set to get the values
    const UGBG_Attribute_Set *gbg_attribute_set = Cast<UGBG_Attribute_Set>(Attribute_Set);
    if (gbg_attribute_set == 0) return;

    // Broadcast every attribute's current value to the UI
    On_Health_Changed.Broadcast(gbg_attribute_set->Get_Health() );
    On_Max_Health_Changed.Broadcast(gbg_attribute_set->Get_Health_Max() );
    On_Stamina_Changed.Broadcast(gbg_attribute_set->Get_Stamina() );
    On_Max_Stamina_Changed.Broadcast(gbg_attribute_set->Get_Stamina_Max() );
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_HUD_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    Super::Bind_Callbacks_To_Dependencies();

    if (Ability_System_Component == 0 || Attribute_Set == 0) return;

    const UGBG_Attribute_Set* gbg_attribute_set = Cast<UGBG_Attribute_Set>(Attribute_Set);
    if (gbg_attribute_set == 0) return;

    // Subscribe our local functions to the GAS delegates that fire on attribute change
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(gbg_attribute_set->GetHealthAttribute() ).AddUObject(this, &UGBUI_HUD_Widget_Controller::Health_Changed);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(gbg_attribute_set->GetMaxHealthAttribute() ).AddUObject(this, &UGBUI_HUD_Widget_Controller::Max_Health_Changed);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(gbg_attribute_set->GetStaminaAttribute() ).AddUObject(this, &UGBUI_HUD_Widget_Controller::Stamina_Changed);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(gbg_attribute_set->GetMaxStaminaAttribute() ).AddUObject(this, &UGBUI_HUD_Widget_Controller::Max_Stamina_Changed);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_HUD_Widget_Controller::Health_Changed(const FOnAttributeChangeData& data)
{
    On_Health_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_HUD_Widget_Controller::Max_Health_Changed(const FOnAttributeChangeData& data)
{
    On_Max_Health_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_HUD_Widget_Controller::Stamina_Changed(const FOnAttributeChangeData& data)
{
    On_Stamina_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_HUD_Widget_Controller::Max_Stamina_Changed(const FOnAttributeChangeData& data)
{
    On_Max_Stamina_Changed.Broadcast(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------
