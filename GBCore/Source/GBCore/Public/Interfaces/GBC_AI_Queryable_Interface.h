//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "GBC_AI_Queryable_Interface.generated.h"
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI) class UGBC_AI_Queryable_Interface : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class GBCORE_API IGBC_AI_Queryable_Interface
{
	GENERATED_BODY()

public:
    /**
	 * @brief Запрашивает у объекта числовое значение, связанное с тегом.
	 * @param DataTag Тег, описывающий данные (например, "Data.Nutrition", "Data.Weight").
	 * @param OutValue Сюда будет записан результат, если он найден.
	 * @return true, если объект смог предоставить данные по этому тегу.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI|Query") bool Query_Float_Value_By_Tag(FGameplayTag data_tag, float& out_value) const;
};
//------------------------------------------------------------------------------------------------------------
