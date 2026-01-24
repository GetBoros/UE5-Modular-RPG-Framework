//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Controller.h>
#include <Abilities/TLG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Controller
void UTLG_Widget_Controller::Broadcast_Initial_Values()
{
    UTLG_Attribute_Set* as = Get_TLG_Attribute_Set();
    if (as != 0)
    {
        Sanity_Prev = as->GetSanity();
        Dominance_Prev = as->GetDominance();

        On_Sanity_Changed.Broadcast(Sanity_Prev, 0.0f);
        On_Dominance_Changed.Broadcast(Dominance_Prev, 0.0f);
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    UTLG_Attribute_Set* as = Get_TLG_Attribute_Set();
    if (Ability_System_Component != 0 && as != 0)
    {
        Ability_System_Component->GetGameplayAttributeValueChangeDelegate(as->GetSanityAttribute())
            .AddUObject(this, &UTLG_Widget_Controller::Handle_Sanity_Changed);

        Ability_System_Component->GetGameplayAttributeValueChangeDelegate(as->GetDominanceAttribute())
            .AddUObject(this, &UTLG_Widget_Controller::Handle_Dominance_Changed);
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Sanity_Changed(const FOnAttributeChangeData& data)
{
    float current = data.NewValue;
    float delta = (Sanity_Prev >= 0.0f) ? (current - Sanity_Prev) : 0.0f;

    Sanity_Prev = current;
    On_Sanity_Changed.Broadcast(current, delta);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Dominance_Changed(const FOnAttributeChangeData& data)
{
    float current = data.NewValue;
    float delta = (Dominance_Prev >= 0.0f) ? (current - Dominance_Prev) : 0.0f;

    Dominance_Prev = current;
    On_Dominance_Changed.Broadcast(current, delta);
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set* UTLG_Widget_Controller::Get_TLG_Attribute_Set() const
{
    return Cast<UTLG_Attribute_Set>(Attribute_Set);
}
//------------------------------------------------------------------------------------------------------------