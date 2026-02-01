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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Text_Button;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Target;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Action
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Action_Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Time_Cost_Minutes = 15;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Action_Tag;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTagContainer Required_Tags;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Data_Location : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0") ) float Enemy_Encounter_Chance = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTagContainer Gameplay_Tag_Container_Events_Possible;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Text_Location_Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTexture2D> Texture2D_Background_Image;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<USoundBase> SoundBase_Ambient;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Exit> TLG_Location_Exits;
};
//------------------------------------------------------------------------------------------------------------
