//------------------------------------------------------------------------------------------------------------
#include <GAS/TLG_Ability_Set.h>
#include <GAS/TLG_Gameplay_Ability.h>

#include <AbilitySystemComponent.h>
#include <GameplayAbilitySpec.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Ability_Set
void UTLG_Ability_Set::Give_To_Ability_System(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	// 1.0. Give abilities
	for (const FTLG_Ability_Bind_Info &tlg_ability_bind_info: Granted_Abilities)
	{
		int32 input_id = 0;
		UGBG_Gameplay_Ability *ability_cdo;
		TSubclassOf<UTLG_Gameplay_Ability> ability_class = tlg_ability_bind_info.Ability_Class;

		if (tlg_ability_bind_info.Ability_Class == 0)
			continue;

		ability_cdo = ability_class->GetDefaultObject<UGBG_Gameplay_Ability>();  // Get Input id from ability template
		if (ability_cdo != 0)
			input_id = ability_cdo->Input_ID;

		FGameplayAbilitySpec ability_spec(tlg_ability_bind_info.Ability_Class, 1, input_id, object_source);

		if (tlg_ability_bind_info.Input_Tag.IsValid())
			ability_spec.GetDynamicSpecSourceTags().AddTag(tlg_ability_bind_info.Input_Tag);  // Добавляем динамический тег для активации (если используем теги вместо инпутов)

		ability_system_component->GiveAbility(ability_spec);
	}

	// 2.0.	Apply passive effects
	for (const TSubclassOf<UGameplayEffect>& effect_class : Granted_Effects)
	{
		if (effect_class == 0)
			continue;

		FGameplayEffectContextHandle context_handle = ability_system_component->MakeEffectContext();
	
		context_handle.AddSourceObject(object_source);

		FGameplayEffectSpecHandle spec_handle = ability_system_component->MakeOutgoingSpec(effect_class, 1.0f, context_handle);
		
		if (spec_handle.IsValid())
			ability_system_component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get());
	}
}
//------------------------------------------------------------------------------------------------------------
