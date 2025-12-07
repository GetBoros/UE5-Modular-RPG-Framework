//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "EnvironmentQuery/EnvQueryTest.h"
#include "GB_AI_EQS.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API UGB_AI_EQS : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UGB_AI_EQS();

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
//------------------------------------------------------------------------------------------------------------
