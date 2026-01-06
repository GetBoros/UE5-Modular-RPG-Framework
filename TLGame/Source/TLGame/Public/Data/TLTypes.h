//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "TLTypes.generated.h"
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EDialogueResponseCategory : uint8
{
    Aggressive UMETA(DisplayName = "Aggressive (Red)"),
    Submissive UMETA(DisplayName = "Submissive (Green)"),
    Logical UMETA(DisplayName = "Logical (Blue)"),
    Silent UMETA(DisplayName = "Silent (Grey)")
};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FPlayerResponse
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") float SanityCost = 0.0f;  // Стоимость выбора Например: Требует Sanity > 10 Тут можно будет расширить логику позже
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FText ResponseText;  // Текст на кнопке: "Закрой рот!"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") EDialogueResponseCategory Category = EDialogueResponseCategory::Aggressive;  // Категория (влияет на визуал кнопки)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") FGameplayTagContainer ApplyTags;  // Тэги, которые этот ответ добавляет (Эффекты) // Например: State.Enemy.Mood.Broken

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FDialogueNode : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Уникальный ID для дебага
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName RowID;

    // Текст Врага: "Ты опять пялился на ту кассиршу!"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (MultiLine = true))
    FText NPC_Line;

    // Картинка эмоции (опционально, если хотим хардкод, но лучше через теги)
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
    // UTexture2D* PortraitOverride;

    // Требования для показа этого узла (если используем рандом)
    // Например: Враг должен быть Angry
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conditions")
    FGameplayTagContainer RequiredConditions;

    // Список ответов Игрока
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TArray<FPlayerResponse> PlayerResponses;
};
//------------------------------------------------------------------------------------------------------------
