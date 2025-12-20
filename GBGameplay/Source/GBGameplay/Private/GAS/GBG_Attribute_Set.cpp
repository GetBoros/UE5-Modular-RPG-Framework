//------------------------------------------------------------------------------------------------------------
#include <GAS/GBG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
#include <Net/UnrealNetwork.h>
//------------------------------------------------------------------------------------------------------------




// UGBG_Attribute_Set
UGBG_Attribute_Set::UGBG_Attribute_Set()
{

}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, Health_Max, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, Stamina_Max, COND_None, REPNOTIFY_Always);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Init_Health(float new_val)
{
	Health.SetBaseValue(new_val);
	Health.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Init_Stamina(float new_val)
{
	Stamina.SetBaseValue(new_val);
	Stamina.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Init_Health_Max(float new_val)
{
	Health_Max.SetBaseValue(new_val);
	Health_Max.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Init_Stamina_Max(float new_val)
{
	Stamina_Max.SetBaseValue(new_val);
	Stamina_Max.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Set_Health(float new_val)
{
	UAbilitySystemComponent *asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
		asc->SetNumericAttributeBase(GetHealthAttribute(), new_val);  // Right way to change value
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Set_Health_Max(float new_val)
{
	UAbilitySystemComponent *asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
		asc->SetNumericAttributeBase(GetMaxHealthAttribute(), new_val);  // Right way to change value
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Set_Stamina(float new_val)
{
	UAbilitySystemComponent *asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
		asc->SetNumericAttributeBase(GetStaminaAttribute(), new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Set_Stamina_Max(float new_val)
{
	UAbilitySystemComponent *asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
		asc->SetNumericAttributeBase(GetMaxStaminaAttribute(), new_val);
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::Get_Health() const
{
	return Health.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::Get_Health_Max() const
{
	return Health_Max.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::Get_Stamina() const
{
	return Stamina.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::Get_Stamina_Max() const
{
	return Stamina_Max.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute UGBG_Attribute_Set::GetHealthAttribute()
{
	static FProperty *property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Health) );  // Find property in class and return as FGameplayAttribute

	return FGameplayAttribute(property);
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute UGBG_Attribute_Set::GetMaxHealthAttribute()
{
	static FProperty *property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Health_Max) );  // Find property in class and return as FGameplayAttribute

	return FGameplayAttribute(property);
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute UGBG_Attribute_Set::GetStaminaAttribute()
{
	static FProperty *property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Stamina) );

	return FGameplayAttribute(property);
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute UGBG_Attribute_Set::GetMaxStaminaAttribute()
{
	static FProperty *property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Stamina_Max) );

	return FGameplayAttribute(property);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Health(const FGameplayAttributeData &old_health)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Health, old_health);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Health_Max(const FGameplayAttributeData &old_health_max)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Health_Max, old_health_max);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Stamina(const FGameplayAttributeData &old_stamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Stamina, old_stamina);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Stamina_Max(const FGameplayAttributeData &old_stamina_max)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Stamina_Max, old_stamina_max);
}
//------------------------------------------------------------------------------------------------------------
