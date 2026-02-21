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
USTRUCT(BlueprintType) struct FTLG_Set_By_Caller_Magnitude
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Attribute_Tag;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Attribute_Magnitude = 0.0f;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FTLG_Action_Requirement
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ETLG_Requirement_Type Requirement_Type = ETLG_Requirement_Type::Attribute_Greater_Equal;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement_Type == ETLG_Requirement_Type::Attribute_Greater_Equal || Requirement_Type == ETLG_Requirement_Type::Attribute_Less_Equal") )
    FGameplayAttribute Attribute;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement_Type == ETLG_Requirement_Type::Attribute_Greater_Equal || Requirement_Type == ETLG_Requirement_Type::Attribute_Less_Equal") )
    float Value = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Requirement_Type == ETLG_Requirement_Type::Has_Gameplay_Tag || Requirement_Type == ETLG_Requirement_Type::Missing_Gameplay_Tag") )
    FGameplayTag Attribute_Tag;
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Action_Requirement> Action_Requirement;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTLG_Set_By_Caller_Magnitude> Set_By_Caller_Magnitude;
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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Action> TLG_Location_Actions;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<FTLG_Location_Enemy> TLG_Location_Enemies;

};
//------------------------------------------------------------------------------------------------------------
