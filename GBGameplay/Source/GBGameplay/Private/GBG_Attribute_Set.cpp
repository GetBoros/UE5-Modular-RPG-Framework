//------------------------------------------------------------------------------------------------------------
#include <GBG_Attribute_Set.h>
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
FGameplayAttribute UGBG_Attribute_Set::GetStaminaAttribute()
{
	// Этот код находит C++ свойство "Stamina" в классе и возвращает его как FGameplayAttribute
	static FProperty* Property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Stamina));
	return FGameplayAttribute(Property);
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::GetStamina() const
{
	return Stamina.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::SetStamina(float new_val)
{
	UAbilitySystemComponent* asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
	{
		// Правильный способ изменить базовое значение атрибута
		asc->SetNumericAttributeBase(GetStaminaAttribute(), new_val);
	}
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::InitStamina(float new_val)
{
	// Этот метод используется для первоначальной установки значения, до начала игры
	Stamina.SetBaseValue(new_val);
	Stamina.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute UGBG_Attribute_Set::GetMaxStaminaAttribute()
{
	static FProperty *property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, Stamina_Max) );
	return FGameplayAttribute(property);
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::GetMaxStamina() const
{
	return Stamina_Max.GetCurrentValue();
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::SetMaxStamina(float new_val)
{
	UAbilitySystemComponent* asc = GetOwningAbilitySystemComponent();
	if (asc != 0)
	{
		asc->SetNumericAttributeBase(GetMaxStaminaAttribute(), new_val);
	}
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::InitMaxStamina(float new_val)
{
	Stamina_Max.SetBaseValue(new_val);
	Stamina_Max.SetCurrentValue(new_val);
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
