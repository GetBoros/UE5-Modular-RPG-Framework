//------------------------------------------------------------------------------------------------------------
#include <GAS/TLG_Ability_Set.h>
#include <GAS/TLG_Gameplay_Ability.h>

#include <AbilitySystemComponent.h>
#include <GameplayAbilitySpec.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Ability_Set
void UTLG_Ability_Set::Init(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	Give_Abilities_Binded(ability_system_component, object_source);
	Give_Effects_Passive(ability_system_component, object_source);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Ability_Set::Give_Effects_Passive(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	FGameplayEffectSpecHandle spec_handle;
	FGameplayEffectContextHandle context_handle;

	for (const TSubclassOf<UGameplayEffect> &effect_class : Granted_Effects)
	{
		context_handle = ability_system_component->MakeEffectContext();
		context_handle.AddSourceObject(object_source);
		spec_handle = ability_system_component->MakeOutgoingSpec(effect_class, 1.0f, context_handle);
		if (spec_handle.IsValid() == true)
			ability_system_component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get() );
	}

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Ability_Set::Give_Abilities_Binded(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	TSubclassOf<UTLG_Gameplay_Ability> tlg_gameplay_ability_class;
	FGameplayAbilitySpec gameplay_ability_spec;

	for (const FTLG_Ability_Bind_Info &tlg_ability_bind_info: TLG_Ability_Bind_Info_Array)
	{
		tlg_gameplay_ability_class = tlg_ability_bind_info.TLG_Gameplay_Ability_Class;

		gameplay_ability_spec = FGameplayAbilitySpec(tlg_gameplay_ability_class, 1, -1, object_source);
		if (tlg_ability_bind_info.Input_Tag.IsValid() == true)
			gameplay_ability_spec.GetDynamicSpecSourceTags().AddTag(tlg_ability_bind_info.Input_Tag);

		ability_system_component->GiveAbility(gameplay_ability_spec);
	}
}
//------------------------------------------------------------------------------------------------------------
