//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/StateTreeConditionBlueprintBase.h>

#include <TLG_STC_Story_Flag_Check.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_STC_Story_Flag_Check : public UStateTreeConditionBlueprintBase
{
	GENERATED_BODY()
	
public:
	virtual bool TestCondition(FStateTreeExecutionContext &context) const;
	virtual bool ReceiveTestCondition() const;

	UPROPERTY(EditAnywhere, Category = "Condition") FGameplayTag Flag;
};
//------------------------------------------------------------------------------------------------------------
