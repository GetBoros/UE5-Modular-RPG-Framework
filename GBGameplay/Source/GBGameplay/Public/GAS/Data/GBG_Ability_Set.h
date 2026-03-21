//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <GBG_Ability_Set.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBG_Gameplay_Ability;
class UGameplayEffect;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGBG_Ability_Set_Bind_Info
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) TSubclassOf<UGBG_Gameplay_Ability> GBG_Gameplay_Ability_Class;
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) FGameplayTag Dynamic_Spec_Source_Tag;  // Used with GetDynamicSpecSourceTags

};
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_Ability_Set : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	void Grant_To_Ability_System(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;  // Apply abilities and passive effects to ability system component

private:
    void Grant_Abilities_Binded(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;  // Add abilities to ability system component
    void Grant_Effects_Passive(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;  // Add passive effects to ability system component

     UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TArray<FGBG_Ability_Set_Bind_Info> GBG_Ability_Set_Bind_Info;
     UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TArray<TSubclassOf<UGameplayEffect> > Granted_Gameplay_Effects;

};
//------------------------------------------------------------------------------------------------------------
