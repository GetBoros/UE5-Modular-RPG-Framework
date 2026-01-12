//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayTagContainer.h>
#include <Engine/DataTable.h>

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
USTRUCT(BlueprintType) struct FPlayer_Response
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") EDialogue_Response_Category Category = EDialogue_Response_Category::Aggressive;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") float Sanity_Cost = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FName Next_Row_ID;  // Next response ID if none dialogue end
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FText Response_Text;  // Text on button example "Stop talk"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FGameplayTagContainer Apply_Tags;  // Add tag on response

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDialogue_Node : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conditions") FGameplayTagContainer Required_Conditions;  // Condition, if has tag can add additional response
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (MultiLine = true) ) FText NPC_Line;  // Oponent text "Are you say something"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") TArray<FPlayer_Response> Player_Responses;  // Response list
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FName Row_ID;
    
};
//------------------------------------------------------------------------------------------------------------
