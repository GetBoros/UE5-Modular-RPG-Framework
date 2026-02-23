//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/StateTreeEvaluatorBlueprintBase.h>

#include <TLG_STE_Core_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_Player_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_STE_Core_Enemy : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()

public:
	virtual void TreeStart(FStateTreeExecutionContext &context);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output") TObjectPtr<ATLG_Player_Controller> TLG_Player_Controller = 0;
};
//------------------------------------------------------------------------------------------------------------
