//------------------------------------------------------------------------------------------------------------
#include <Abilities/TLG_Attribute_Set.h>
#include <GameplayEffectExtension.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Attribute_Set
UTLG_Attribute_Set::UTLG_Attribute_Set()
{
    // Default values can re-init in Data table later
    InitSanity(100.0f);
    InitSanity_Max(100.0f);
    InitDominance(0.0f);
    InitEmpathy(0.0f);
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
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Attribute_Set::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &data)
{
    Super::PostGameplayEffectExecute(data);

    if (data.EvaluatedData.Attribute == GetSanityAttribute() )
    {
        const float current_sanity = GetSanity();

        if (current_sanity <= 0.0f)
        {
            int yy = 0;

            yy++;  // TODO: Send Gameplay Event: Game Over (Psych Ward)
        }
    }
}
//------------------------------------------------------------------------------------------------------------