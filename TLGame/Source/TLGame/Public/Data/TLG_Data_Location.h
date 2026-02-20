//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>
#include <AttributeSet.h>

#include <TLG_Data_Location.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTexture2D;
class USoundBase;
class UDataTable;
class UGameplayEffect;
class UTLG_Data_Enemy;
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ETLG_Requirement_Type : uint8
{
    Attribute_Greater_Equal,
    Attribute_Less_Equal,
    Has_Gameplay_Tag,
    Missing_Gameplay_Tag
};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Requirement
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) bool Is_Higher = true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float Value = 0.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTag Gameplay_Tag;
};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Magnitude_Tag_Pair
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere) float Magnitude = 0.f;
    UPROPERTY(EditAnywhere) FGameplayTag Gameplay_Tag;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Button_Settings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) ETLG_Requirement_Type Requirement = ETLG_Requirement_Type::Attribute_Greater_Equal;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement == ETLG_Requirement_Type::Attribute_Greater_Equal || Requirement == ETLG_Requirement_Type::Attribute_Less_Equal") )
    FGameplayAttribute Attribute;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement == ETLG_Requirement_Type::Attribute_Greater_Equal || Requirement == ETLG_Requirement_Type::Attribute_Less_Equal") )
    float Value = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement == ETLG_Requirement_Type::Has_Gameplay_Tag || Requirement == ETLG_Requirement_Type::Missing_Gameplay_Tag") )
    FGameplayTag Gameplay_Tag;
};
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Text_Button;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Time_Cost_Minutes = 15;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Gameplay_Tag_Action;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Button_Settings> TLG_Button_Settings;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Magnitude_Tag_Pair> TLG_Magnitude_Tag_Pair_Array;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Requirement> TLG_Location_Action_Requirement;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Location_Enemy
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0") ) float Encounter_Chance = 0.5f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UTLG_Data_Enemy> TLG_Data_Enemy;

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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Enemy> TLG_Location_Enemies;

};
//------------------------------------------------------------------------------------------------------------
