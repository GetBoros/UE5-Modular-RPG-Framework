//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <EnvironmentQuery/EnvQueryTest.h>
#include "GameplayTagContainer.h"

#include "EQT_Temp.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API UEQT_Temp : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEQT_Temp();
	
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const;  // Основная функция теста, которую вызывает EQS
	virtual FText GetDescriptionTitle() const;  // Текст, который будет отображаться на ноде в редакторе EQS
	virtual FText GetDescriptionDetails() const;

protected:
	UPROPERTY(EditAnywhere, Category = "Tags") FGameplayTag TagToMatch;  // Переменная, которую мы будем настраивать в редакторе EQS
};
//------------------------------------------------------------------------------------------------------------
