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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") float Sanity_Cost = 0.0f;  // Стоимость выбора Например: Требует Sanity > 10 Тут можно будет расширить логику позже
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") EDialogue_Response_Category Category = EDialogue_Response_Category::Aggressive;  // Категория (влияет на визуал кнопки)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FText Response_Text;  // Текст на кнопке: "Закрой рот!"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FGameplayTagContainer Apply_Tags;  // Тэги, которые этот ответ добавляет (Эффекты) // Например: State.Enemy.Mood.Broken

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDialogue_Node : public FTableRowBase
{
    GENERATED_BODY()

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (MultiLine = true) ) FText NPC_Line;  // Текст Врага: "Ты опять пялился на ту кассиршу!"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conditions") FGameplayTagContainer Required_Conditions;  // Требования для показа этого узла (если используем рандом) Например: Враг должен быть Angry1
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") TArray<FPlayer_Response> Player_Responses;  // Список ответов Игрока
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FName Row_ID;
    
};
//------------------------------------------------------------------------------------------------------------
