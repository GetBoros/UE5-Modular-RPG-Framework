//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <TLG_Ability_Set.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Gameplay_Ability;
class UGameplayEffect;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Ability_Bind_Info
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "TLG|Abilities") TSubclassOf<UTLG_Gameplay_Ability> Ability_Class;
    UPROPERTY(EditDefaultsOnly, Category = "TLG|Abilities") FGameplayTag Input_Tag;

};
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType, Const) class TLGAME_API UTLG_Ability_Set : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    void Give_To_Ability_System(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;
  
    UPROPERTY(EditDefaultsOnly) TArray<FTLG_Ability_Bind_Info> Granted_Abilities;
    UPROPERTY(EditDefaultsOnly) TArray<TSubclassOf<UGameplayEffect>> Granted_Effects;
    
};
//------------------------------------------------------------------------------------------------------------
