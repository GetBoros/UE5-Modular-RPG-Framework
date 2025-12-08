//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
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
};
//------------------------------------------------------------------------------------------------------------
