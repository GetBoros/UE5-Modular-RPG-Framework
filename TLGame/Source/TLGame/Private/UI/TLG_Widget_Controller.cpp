//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Controller.h>
#include <Abilities/TLG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Controller
void UTLG_Widget_Controller::Broadcast_Initial_Values()
{
    UTLG_Attribute_Set *tlg_attribute_set = Get_TLG_Attribute_Set();

    if (tlg_attribute_set == 0)
        return;

    Prev_Sanity = tlg_attribute_set->GetSanity();
    Prev_Dominance = tlg_attribute_set->GetDominance();

    On_Changed_Sanity.Broadcast(Prev_Sanity, 0.0f);
    On_Changed_Dominance.Broadcast(Prev_Dominance, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    UTLG_Attribute_Set *tlg_attribute_set = Get_TLG_Attribute_Set();

    if (Ability_System_Component == 0 || tlg_attribute_set == 0)
        return;

    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Sanity);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Dominance);

    if (Attribute_Info != 0)  // Нашли инфу про Sanity (иконку, название) // Можем отправить эту инфу в UI, если нужно обновить иконку динамически
        FGBC_Attribute_Info_Item SanityInfo = Attribute_Info->Find_Attribute_Info_By_Tag(FGameplayTag::RequestGameplayTag("Attribute.Player.Sanity") );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Sanity(const FOnAttributeChangeData &attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
	float delta = 0.0f;
    
    if (Prev_Sanity >= 0.0f)
        delta = current - Prev_Sanity;

    Prev_Sanity = current;

    On_Changed_Sanity.Broadcast(current, delta);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Dominance(const FOnAttributeChangeData &attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
    float delta = 0.0f;

    if (Prev_Dominance >= 0.0f)
        delta = current - Prev_Dominance;

    Prev_Dominance = current;

    On_Changed_Dominance.Broadcast(current, delta);
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *UTLG_Widget_Controller::Get_TLG_Attribute_Set() const
{
    return Cast<UTLG_Attribute_Set>(Attribute_Set);
}
//------------------------------------------------------------------------------------------------------------