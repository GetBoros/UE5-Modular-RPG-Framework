//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <AttributeSet.h>
#include <AbilitySystemComponent.h>

#include <TLG_Attribute_Set.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOn_Attribute_Empty_Signature);
//------------------------------------------------------------------------------------------------------------
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Attribute_Set : public UAttributeSet
{
    GENERATED_BODY()

public:
    UTLG_Attribute_Set();

    virtual void PreAttributeChange(const FGameplayAttribute &attribute, float &new_value) override;  // for clamping
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &data) override;

    mutable FOn_Attribute_Empty_Signature On_Sanity_Zero;

    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Sanity;  // SANITY (HP)
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Sanity);

    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Sanity_Max;
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Sanity_Max);
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Dominance;  // DOMINANCE (Mana/Strength)
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Dominance);
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Empathy;  // EMPATHY (Corruption)
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Empathy);

    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Fatigue; // 0 - good, 100 - dead
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Fatigue);

    UPROPERTY(BlueprintReadOnly, Category = "Attributes") FGameplayAttributeData Fatigue_Max;
    ATTRIBUTE_ACCESSORS(UTLG_Attribute_Set, Fatigue_Max);
};
//------------------------------------------------------------------------------------------------------------