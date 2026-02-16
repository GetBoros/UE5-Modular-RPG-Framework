//------------------------------------------------------------------------------------------------------------
#include <Abilities/TLG_Attribute_Set.h>
#include <GameplayEffectExtension.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Attribute_Set
UTLG_Attribute_Set::UTLG_Attribute_Set()
{
    InitSanity(100.0f);
    InitSanity_Max(100.0f);

    InitDominance(0.0f);

    InitEmpathy(0.0f);

    InitFatigue(0.0f);
    InitFatigue_Max(100.0f);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Attribute_Set::PreAttributeChange(const FGameplayAttribute &attribute, float &new_value)
{
    Super::PreAttributeChange(attribute, new_value);

    if (attribute == GetSanityAttribute() )
        new_value = FMath::Clamp(new_value, 0.0f, GetSanity_Max() );

    if (attribute == GetDominanceAttribute() )
        new_value = FMath::Clamp(new_value, 0.0f, 100.0f);

    if (attribute == GetEmpathyAttribute() )
        new_value = FMath::Clamp(new_value, 0.0f, 100.0f);

    if (attribute == GetFatigueAttribute() )
        new_value = FMath::Clamp(new_value, 0.0f, GetFatigue_Max() );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Attribute_Set::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &data)
{
    Super::PostGameplayEffectExecute(data);

    if (data.EvaluatedData.Attribute == GetSanityAttribute() )
        if (GetSanity() <= 0.0f)
            if (On_Sanity_Zero.IsBound() )
                On_Sanity_Zero.Broadcast();

    if (data.EvaluatedData.Attribute == GetDominanceAttribute() )
        SetDominance(FMath::Clamp(GetDominance(), 0.0f, 100.0f) );

    if (data.EvaluatedData.Attribute == GetEmpathyAttribute() )
        SetEmpathy(FMath::Clamp(GetEmpathy(), 0.0f, 100.0f) );

    if (data.EvaluatedData.Attribute == GetFatigueAttribute())
        SetFatigue(FMath::Clamp(GetFatigue(), 0.0f, GetFatigue_Max() ) );

}
//------------------------------------------------------------------------------------------------------------