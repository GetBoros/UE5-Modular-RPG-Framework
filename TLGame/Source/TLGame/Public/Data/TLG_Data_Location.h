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
class UGameplayEffect;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Exit
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Text_Button;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Target;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Magnitude_Tag_Pair
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere) float Magnitude = 0.f;
    UPROPERTY(EditAnywhere) FGameplayTag DataTag;
};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Action
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Text_Button;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Time_Cost_Minutes = 15;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Gameplay_Tag_Action;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTagContainer Gameplay_Tag_Action_Required;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Magnitude_Tag_Pair> ActionTagValues;
    // UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<UGameplayEffect> Gameplay_Effect_Class;

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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Action> TLG_Location_Action;

};
//------------------------------------------------------------------------------------------------------------
