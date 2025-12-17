//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <AttributeSet.h>
#include <AbilitySystemComponent.h>
#include <GBG_Attribute_Set.generated.h>
//------------------------------------------------------------------------------------------------------------
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_Attribute_Set : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGBG_Attribute_Set();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;  // Important for replication in game

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health) FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGBG_Attribute_Set, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health_Max) FGameplayAttributeData Health_Max;
	ATTRIBUTE_ACCESSORS(UGBG_Attribute_Set, Health_Max);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina) FGameplayAttributeData Stamina;
	static FGameplayAttribute GetStaminaAttribute();  // ATTRIBUTE_ACCESSORS
	float GetStamina() const;
	void SetStamina(float new_val);
	void InitStamina(float new_val);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina_Max) FGameplayAttributeData Stamina_Max;
	static FGameplayAttribute GetMaxStaminaAttribute();
	float GetMaxStamina() const;
	void SetMaxStamina(float new_val);
	void InitMaxStamina(float new_val);

protected:
	UFUNCTION() virtual void OnRep_Health(const FGameplayAttributeData &old_health);
	UFUNCTION() virtual void OnRep_Health_Max(const FGameplayAttributeData &old_health_max);
	UFUNCTION() virtual void OnRep_Stamina(const FGameplayAttributeData &old_stamina);
	UFUNCTION() virtual void OnRep_Stamina_Max(const FGameplayAttributeData &old_stamina_max);
};
//------------------------------------------------------------------------------------------------------------