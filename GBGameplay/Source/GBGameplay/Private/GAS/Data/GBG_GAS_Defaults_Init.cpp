//------------------------------------------------------------------------------------------------------------
#include <GAS/Data/GBG_GAS_Defaults_Init.h>
#include <GAS/GBG_Gameplay_Ability.h>

#include <AbilitySystemComponent.h>
#include <GameplayAbilitySpec.h>
//------------------------------------------------------------------------------------------------------------




// UGBG_Ability_Set 
void UGBG_Ability_Set::Grant_To_Ability_System(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	Grant_Abilities_Binded(ability_system_component, object_source);
	Grant_Effects_Passive(ability_system_component, object_source);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Ability_Set::Grant_Abilities_Binded(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	TSubclassOf<UGBG_Gameplay_Ability> tlg_gameplay_ability_class;
	FGameplayAbilitySpec gameplay_ability_spec;

	for (const FGBG_Ability_Bind_Info &tlg_ability_bind_info: TLG_Ability_Bind_Info_Array)
	{
		tlg_gameplay_ability_class = tlg_ability_bind_info.GBG_Gameplay_Ability_Class;
		gameplay_ability_spec = FGameplayAbilitySpec(tlg_gameplay_ability_class, 1, -1, object_source);
		
		if (tlg_ability_bind_info.Dynamic_Spec_Source_Tag.IsValid() == true)
			gameplay_ability_spec.GetDynamicSpecSourceTags().AddTag(tlg_ability_bind_info.Dynamic_Spec_Source_Tag);

		ability_system_component->GiveAbility(gameplay_ability_spec);
	}
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Ability_Set::Grant_Effects_Passive(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
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
