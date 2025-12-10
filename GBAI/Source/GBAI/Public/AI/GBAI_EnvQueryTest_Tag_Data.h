//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayTagContainer.h>
#include <DataProviders/AIDataProvider.h>
#include <EnvironmentQuery/EnvQueryTest.h>

#include <GBAI_EnvQueryTest_Tag_Data.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API UGBAI_EnvQueryTest_Tag_Data : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UGBAI_EnvQueryTest_Tag_Data();

	virtual void RunTest(FEnvQueryInstance &query_instance) const;
	virtual FText GetDescriptionTitle() const;
	virtual FText GetDescriptionDetails() const;

    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag Tag_Required;  // CHANGE: Must be in Actor to see
    UPROPERTY(EditAnywhere, Category = "Test") FGameplayTag Tag_Data_To_Query;  // CHANGE: Data Tag, we want to get some differents data
    UPROPERTY(EditAnywhere, Category = "Test") FAIDataProviderFloatValue Score_Multiplier;  // CHANGE: Multiplier, can change or receive from StateTree or other
};
//------------------------------------------------------------------------------------------------------------
