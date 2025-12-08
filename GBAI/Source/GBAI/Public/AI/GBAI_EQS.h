//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameplayTagContainer.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "GBAI_EQS.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API UGBAI_EQS : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UGBAI_EQS();

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;

    // CHANGE: Тег, который должен быть у объекта (например, "Item.Consumable.Food")
    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag RequiredTag;
    // CHANGE: Тег данных, которые мы хотим получить (например, "Data.Value.Nutrition")
    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag DataToQueryTag;
    // CHANGE: Множитель, который можно передать из StateTree/BT (например, фактор голода)
    UPROPERTY(EditAnywhere, Category = "Test") FAIDataProviderFloatValue ScoreMultiplier;
};
//------------------------------------------------------------------------------------------------------------
