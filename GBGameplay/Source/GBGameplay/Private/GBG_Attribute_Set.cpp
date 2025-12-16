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
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGBG_Attribute_Set, MaxStamina, COND_None, REPNOTIFY_Always);
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
	static FProperty* Property = FindFieldChecked<FProperty>(UGBG_Attribute_Set::StaticClass(), GET_MEMBER_NAME_CHECKED(UGBG_Attribute_Set, MaxStamina));
	return FGameplayAttribute(Property);
}
//------------------------------------------------------------------------------------------------------------
float UGBG_Attribute_Set::GetMaxStamina() const
{
	return MaxStamina.GetCurrentValue();
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
	MaxStamina.SetBaseValue(new_val);
	MaxStamina.SetCurrentValue(new_val);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Health(const FGameplayAttributeData &old_health)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Health, old_health);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_MaxHealth(const FGameplayAttributeData &old_max_health)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, MaxHealth, old_max_health);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_Stamina(const FGameplayAttributeData& old_stamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, Stamina, old_stamina);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::OnRep_MaxStamina(const FGameplayAttributeData& old_max_stamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGBG_Attribute_Set, MaxStamina, old_max_stamina);
}
//------------------------------------------------------------------------------------------------------------
