//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>

#include <TLG_Data_Location.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Data_Enemy;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Enemy
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TSubclassOf<AActor> Enemy_Class;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTagQuery Spawn_Conditions_Tag_Query;  // ALL(HasTag(Time.Morning), NoTag(Story.Marina.QuestComplete))
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0") ) float Encounter_Chance = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTLG_Data_Enemy> TLG_Data_Enemy;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(BlueprintType) class TLGAME_API UTLG_Data_Location : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTagContainer Gameplay_Tag_Container_Events_Possible;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Text_Location_Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTexture2D> Texture2D_Background_Image;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<USoundBase> SoundBase_Ambient;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Exit> TLG_Location_Exits;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Action> TLG_Location_Actions;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Enemy> TLG_Location_Enemies;

};
//------------------------------------------------------------------------------------------------------------
