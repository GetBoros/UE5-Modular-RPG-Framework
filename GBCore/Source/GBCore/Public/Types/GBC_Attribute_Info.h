//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>
#include <AttributeSet.h>
#include <GBC_Attribute_Info.generated.h>
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGBC_Attribute_Info_Item  // 1. Структура одной записи (Строка таблицы)
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTag Attribute_Tag = FGameplayTag();  // Ключ поиска (например, Attributes.Vitality.Stamina)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayAttribute Attribute_To_Bind;  // Сам атрибут (выбирается из выпадающего списка)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Attribute_Name = FText();  // Имя для UI (например, "Выносливость")
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBC_Attribute_Info : public UDataAsset
{
    GENERATED_BODY()

public:
    FGBC_Attribute_Info_Item Find_Attribute_Info_By_Tag(const FGameplayTag &tag, bool b_log_not_found = false) const;  // Функция-помощник: Найти атрибут по тегу

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config") TArray<FGBC_Attribute_Info_Item> Attribute_Information;
};
//------------------------------------------------------------------------------------------------------------