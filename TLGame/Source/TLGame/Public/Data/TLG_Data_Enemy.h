//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <TLG_Data_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
class UDataTable;
class UTexture2D;
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Data_Enemy : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Name;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UTexture2D>> Portraits;  // !!! TEMP Portrets can be choosen by Gameplay tags
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UDataTable>> Dialogue_Tables;  // Choose DataTable by GameplayTags (Stage.Intro)

    UTexture2D *Get_Portrait_By_Tag(const FGameplayTag &tag) const;
    UDataTable *Get_Dialogue_Table_By_Tag(const FGameplayTag &tag) const;};
//------------------------------------------------------------------------------------------------------------
