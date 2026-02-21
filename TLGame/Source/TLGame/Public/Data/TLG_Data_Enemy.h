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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Enemy_Name;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTag Active_Scenario_Tag;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UTexture2D> > Portraits_By_Scenario;  // !!! TEMP Portrets can be choosen by Gameplay tags
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UDataTable> > Dialogues_By_Scenario;  // Choose DataTable by GameplayTags (Stage.Intro)

    UTexture2D *Get_Portrait_For_Mood(const FGameplayTag &gameplay_tag_mood) const;
    UDataTable *Get_Dialogue_Table_For_Scenario(const FGameplayTag &gameplay_tag_scenario) const;
};
//------------------------------------------------------------------------------------------------------------
