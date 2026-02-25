//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataTable.h>
#include <GameplayTagContainer.h>  // !!! TEMP
#include <AttributeSet.h>  // FTLG_Action_Requirement

#include <TLG_Types.generated.h>
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EDialogue_Response_Category : uint8
{
    Aggressive UMETA(DisplayName = "Aggressive (Red)"),
    Submissive UMETA(DisplayName = "Submissive (Green)"),
    Logical UMETA(DisplayName = "Logical (Blue)"),
    Silent UMETA(DisplayName = "Silent (Grey)")

};
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ETLG_Requirement_Type : uint8
{
    Attribute_Greater_Equal,
    Attribute_Less_Equal,
    Has_Gameplay_Tag,
    Missing_Gameplay_Tag
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
USTRUCT(BlueprintType) struct FTLG_Set_By_Caller_Magnitude
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Attribute_Tag;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Attribute_Magnitude = 0.0f;

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
USTRUCT(BlueprintType) struct FTLG_Location_Exit
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Text_Button;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<class UTLG_Data_Location> TLG_Data_Location_Target;
};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FPlayer_Response
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDialogue_Response_Category Category = EDialogue_Response_Category::Aggressive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Response_Cost = 0.0f;  // Based on category can affect different attribute
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Row_ID_Next;  // Next response ID if none dialogue end
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Text_Response;  // Text on button example "Stop talk"
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer Tags_Apply;  // Add tag on response

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDialogue_Node : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Row_ID;  // ID for Next data table row
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Text_Name_Speaker;  // Main hero or enemy
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true) ) FText Text_NPC_Line;  // Oponent text "Are you say something"

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Tag_Portrait;  // Visual.Portrait.Angry
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Tag_Sound;  // Audio.SFX.Scream
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer Required_Conditions;  // Condition, if has tag can add additional response
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FPlayer_Response> Player_Responses;  // Response list
    
};
//------------------------------------------------------------------------------------------------------------
