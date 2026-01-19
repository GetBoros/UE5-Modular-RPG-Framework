//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayTagContainer.h>
#include <Engine/DataTable.h>

#include <NativeGameplayTags.h>
#include <GameplayTagAssetInterface.h>

#include <TLG_Types.generated.h>
//------------------------------------------------------------------------------------------------------------
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PORTRAIT_AGGRESSIVE)
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EDialogue_Response_Category : uint8
{
    Aggressive UMETA(DisplayName = "Aggressive (Red)"),
    Submissive UMETA(DisplayName = "Submissive (Green)"),
    Logical UMETA(DisplayName = "Logical (Blue)"),
    Silent UMETA(DisplayName = "Silent (Grey)")

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FPlayer_Response
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EDialogue_Response_Category Category = EDialogue_Response_Category::Aggressive;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Sanity_Cost = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Row_ID_Next;  // Next response ID if none dialogue end
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Text_Response;  // Text on button example "Stop talk"
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer Tags_Apply;  // Add tag on response

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDialogue_Node : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Text_Name_Speaker;  // Main hero or enemy
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Tag_Portrait;  // Visual.Portrait.Angry
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Tag_Sound;  // Audio.SFX.Scream

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer Required_Conditions;  // Condition, if has tag can add additional response
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true) ) FText Text_NPC_Line;  // Oponent text "Are you say something"
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FPlayer_Response> Player_Responses;  // Response list
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Row_ID;  // ID for Next data table row
    
};
//------------------------------------------------------------------------------------------------------------
