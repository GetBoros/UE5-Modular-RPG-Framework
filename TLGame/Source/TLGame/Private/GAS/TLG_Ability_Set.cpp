//------------------------------------------------------------------------------------------------------------
#include <GAS/TLG_Ability_Set.h>
#include <GAS/TLG_Gameplay_Ability.h>

#include <AbilitySystemComponent.h>
#include <GameplayAbilitySpec.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Ability_Set
void UTLG_Ability_Set::Give_To_Ability_System(UAbilitySystemComponent *ability_system_component, UObject *object_source) const
{
	int32 input_id = 0;
	UGBG_Gameplay_Ability* ability_cdo;
	TSubclassOf<UTLG_Gameplay_Ability> tlg_gameplay_ability_class;
	FGameplayEffectSpecHandle spec_handle;
	FGameplayEffectContextHandle context_handle;
	FGameplayAbilitySpec gameplay_ability_spec;

	// 1.0. Give abilities
	for (const FTLG_Ability_Bind_Info &tlg_ability_bind_info: TLG_Ability_Bind_Info_Array)
	{
		input_id = 0;
		tlg_gameplay_ability_class = tlg_ability_bind_info.TLG_Gameplay_Ability_Class;
		ability_cdo = tlg_gameplay_ability_class->GetDefaultObject<UGBG_Gameplay_Ability>();  // Get Input id from ability template
		if (ability_cdo != 0)
			input_id = ability_cdo->Input_ID;

		gameplay_ability_spec = FGameplayAbilitySpec(tlg_gameplay_ability_class, 1, input_id, object_source);
		if (tlg_ability_bind_info.Input_Tag.IsValid() )
			gameplay_ability_spec.GetDynamicSpecSourceTags().AddTag(tlg_ability_bind_info.Input_Tag);

		ability_system_component->GiveAbility(gameplay_ability_spec);
	}

	// 2.0.	Apply passive effects
	for (const TSubclassOf<UGameplayEffect> &effect_class : Granted_Effects)
	{
		context_handle = ability_system_component->MakeEffectContext();
		context_handle.AddSourceObject(object_source);
		spec_handle = ability_system_component->MakeOutgoingSpec(effect_class, 1.0f, context_handle);
		if (spec_handle.IsValid() )
			ability_system_component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get() );
	}
}
//------------------------------------------------------------------------------------------------------------
