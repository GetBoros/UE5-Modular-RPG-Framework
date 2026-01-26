//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>

#include <TLG_Data_Location.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTexture2D;
class USoundBase;
class UDataTable;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Exit
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Button_Text;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTLG_Data_Location> Target_Location;

};
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Data_Location : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0") ) float Encounter_Chance = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTagContainer Possible_Events;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Location_Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTexture2D> Background_Image;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<USoundBase> Ambient_Sound;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Exit> TLG_Location_Exits;
};
//------------------------------------------------------------------------------------------------------------
