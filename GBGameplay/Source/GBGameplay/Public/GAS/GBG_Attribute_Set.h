//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <AttributeSet.h>
#include <GBG_Attribute_Set.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_Attribute_Set : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGBG_Attribute_Set();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const;  // Important for replication in game
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &data);  // Effected by some GE

	void Init_Health(float new_val);
	void Init_Health_Max(float new_val);
	void Init_Stamina(float new_val);
	void Init_Stamina_Max(float new_val);
	void Init_Stamina_Threshold(float new_val);

	void Set_Health(float new_val);
	void Set_Health_Max(float new_val);
	void Set_Stamina(float new_val);
	void Set_Stamina_Max(float new_val);
	void Set_Stamina_Threshold(float new_val);

	float Get_Health() const;
	float Get_Health_Max() const;
	float Get_Stamina() const;
	float Get_Stamina_Max() const;
	float Get_Stamina_Threshold() const;

	static FGameplayAttribute GetHealthAttribute();
	static FGameplayAttribute GetMaxHealthAttribute();
	static FGameplayAttribute GetStaminaAttribute();
	static FGameplayAttribute GetMaxStaminaAttribute();
	static FGameplayAttribute GetStaminaThresholdAttribute();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health) FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health_Max) FGameplayAttributeData Health_Max;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina) FGameplayAttributeData Stamina;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina_Max) FGameplayAttributeData Stamina_Max;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina_Threshold) FGameplayAttributeData Stamina_Threshold;

protected:
	UFUNCTION() virtual void OnRep_Health(const FGameplayAttributeData &old_health);
	UFUNCTION() virtual void OnRep_Health_Max(const FGameplayAttributeData &old_health_max);
	UFUNCTION() virtual void OnRep_Stamina(const FGameplayAttributeData &old_stamina);
	UFUNCTION() virtual void OnRep_Stamina_Max(const FGameplayAttributeData &old_stamina_max);
	UFUNCTION() virtual void OnRep_Stamina_Threshold(const FGameplayAttributeData &old_stamina_threshold);

private:
	void Handle_Health_Change(UAbilitySystemComponent *asc);
	void Handle_Stamina_Change(UAbilitySystemComponent *asc);
	void Handle_Stamina_Threshold_Change(UAbilitySystemComponent *asc);

};
//------------------------------------------------------------------------------------------------------------




// REGIONS
#pragma region EXAMPLE_MACROSES

//#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
//	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
//	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
//	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
//	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//ATTRIBUTE_ACCESSORS(UGBG_Attribute_Set, Health);

#pragma endregion
//------------------------------------------------------------------------------------------------------------
