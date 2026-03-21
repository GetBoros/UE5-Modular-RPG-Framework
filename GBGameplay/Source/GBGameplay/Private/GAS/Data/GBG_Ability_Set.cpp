//------------------------------------------------------------------------------------------------------------
#include <GAS/Data/GBG_Ability_Set.h>
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

	for (const FGBG_Ability_Set_Bind_Info &gbg_ability_set_bind_info: GBG_Ability_Set_Bind_Info)  // For each ability in the set, add it to the ability system component
	{
		tlg_gameplay_ability_class = gbg_ability_set_bind_info.GBG_Gameplay_Ability_Class;  // Get ability class from data asset
		gameplay_ability_spec = FGameplayAbilitySpec(tlg_gameplay_ability_class, 1, -1, object_source);  // Create ability spec with default level 1, input ID -1 and source object
		
		if (gbg_ability_set_bind_info.Dynamic_Spec_Source_Tag.IsValid() == true)  // If the dynamic spec source tag is valid, add it to the ability spec's dynamic source tags
			gameplay_ability_spec.GetDynamicSpecSourceTags().AddTag(gbg_ability_set_bind_info.Dynamic_Spec_Source_Tag);  // Can be used for targeting or other things in the ability

		ability_system_component->GiveAbility(gameplay_ability_spec);
	}
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Ability_Set::Grant_Effects_Passive(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	FGameplayEffectSpecHandle spec_handle;
	FGameplayEffectContextHandle context_handle;

	for (const TSubclassOf<UGameplayEffect> &granted_gameplay_effect_class : Granted_Gameplay_Effects)  // For each passive effect in the set, apply it to the ability system component
	{
		context_handle = ability_system_component->MakeEffectContext();  // Create effect context handle
		context_handle.AddSourceObject(object_source);  // Add source object to effect context handle, can be used for targeting or other things in the effect
		spec_handle = ability_system_component->MakeOutgoingSpec(granted_gameplay_effect_class, 1.0f, context_handle);  // Create effect spec handle with default level 1
		if (spec_handle.IsValid() == true)
			ability_system_component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get() );  // Apply effect to self
	}
}
//------------------------------------------------------------------------------------------------------------
