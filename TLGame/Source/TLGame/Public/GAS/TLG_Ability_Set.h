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

    UPROPERTY(EditDefaultsOnly, Category = "TLG|Abilities") TSubclassOf<UTLG_Gameplay_Ability> TLG_Gameplay_Ability_Class;
    UPROPERTY(EditDefaultsOnly, Category = "TLG|Abilities") FGameplayTag Input_Tag;

};
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType, Const) class TLGAME_API UTLG_Ability_Set : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    void Init(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;
  
private:
    void Give_Abilities_Binded(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;
    void Give_Effects_Passive(UAbilitySystemComponent *ability_system_component, UObject *object_source) const;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TArray<FTLG_Ability_Bind_Info> TLG_Ability_Bind_Info_Array;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TArray<TSubclassOf<UGameplayEffect>> Granted_Effects;
    
};
//------------------------------------------------------------------------------------------------------------
