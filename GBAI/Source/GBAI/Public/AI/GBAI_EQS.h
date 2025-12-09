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

	virtual void RunTest(FEnvQueryInstance &query_instance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;

    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag Tag_Required;  // CHANGE: Must be in Actor to see
    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag Tag_Data_To_Query;  // CHANGE: Data Tag, we want to get some differents data
    UPROPERTY(EditAnywhere, Category = "Test") FAIDataProviderFloatValue Score_Multiplier;  // CHANGE: Multiplier, can change or receive from StateTree or other
};
//------------------------------------------------------------------------------------------------------------
