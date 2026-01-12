//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <TLG_Enemy_Data.generated.h>
//------------------------------------------------------------------------------------------------------------
class UDataTable;
class UTexture2D;
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Enemy_Data : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Name;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UTexture2D>> Portraits;  // Portrets can be choosen by Gameplay tags
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UDataTable>> Dialogue_Tables;  // Choose DataTable by GameplayTags (Stage.Intro)

    UDataTable *Get_Table_By_Tag(FGameplayTag tag) const;
};
//------------------------------------------------------------------------------------------------------------
