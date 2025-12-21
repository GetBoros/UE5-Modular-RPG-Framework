//------------------------------------------------------------------------------------------------------------
#include <GAS/GBG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
#include <GameplayEffectExtension.h>
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
void UGBG_Attribute_Set::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &data)
{
    Super::PostGameplayEffectExecute(data);

    FGameplayAttribute attribute = data.EvaluatedData.Attribute;
    UAbilitySystemComponent *asc = GetOwningAbilitySystemComponent();

    if (asc == 0)
        return;

     if (attribute == GetHealthAttribute() )  // Health Logic
		Handle_Health_Change(asc);
	else if (attribute == GetStaminaAttribute() )  // Stamina logic
		Handle_Stamina_Change(asc);
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
void UGBG_Attribute_Set::Handle_Health_Change(UAbilitySystemComponent *asc)
{
	float current_health = Get_Health();
	float max_health = Get_Health_Max();
    float clamped_health = FMath::Clamp(current_health, 0.0f, max_health);
        
    if (current_health != clamped_health)
        Set_Health(clamped_health);

    if (clamped_health <= 0.0f)  // If HP dropped to 0 -> notify owner about death
    {
		// Usually call Character function here: OwnerCharacter->Die(); Or send Gameplay Event "Event.Death"
    }
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Attribute_Set::Handle_Stamina_Change(UAbilitySystemComponent *asc)
{
	float stamina_current = Get_Stamina();
	float stamina_max = Get_Stamina_Max();
    float clamped_stamina = FMath::Clamp(stamina_current, 0.0f, stamina_max);  // B. CLAMPING (Golden Standard): Modify value IMMEDIATELY to prevent "dirty" data
    static FGameplayTag tag_fatigued = FGameplayTag::RequestGameplayTag(FName("State.Fatigued") );  // C. GAMEPLAY LOGIC (Reaction): Cache tag (static var initialized once per game session)

    if (stamina_current != clamped_stamina)  // If value was different (e.g. was -5, became 0) -> update it
        Set_Stamina(clamped_stamina);
        
    if (clamped_stamina <= Stamina_Fatigue_Threshold)  // Example Logic: If stamina < 20% -> apply debuff (In real project 0.2f should be in Config/DataAsset)
	{
		if (asc->HasMatchingGameplayTag(tag_fatigued) != true)  // if tag already added, not add again
			asc->AddLooseGameplayTag(tag_fatigued);
	}
    else
        asc->RemoveLooseGameplayTag(tag_fatigued);
}
//------------------------------------------------------------------------------------------------------------
