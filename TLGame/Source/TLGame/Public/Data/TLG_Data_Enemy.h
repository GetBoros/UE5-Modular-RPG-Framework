//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <TLG_Data_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTexture2D;
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Data_Enemy : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Enemy_Name;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TMap<FGameplayTag, TObjectPtr<UTexture2D> > Portraits_By_Scenario;  // !!! TEMP Portrets can be choosen by Gameplay tags

    UTexture2D *Get_Portrait_For_Mood(const FGameplayTag &gameplay_tag_mood) const;
};
//------------------------------------------------------------------------------------------------------------
