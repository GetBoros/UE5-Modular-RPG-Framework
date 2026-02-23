//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <StateTreeEvaluatorBase.h>

#include <TLG_STE_Core_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_Player_Controller;
//------------------------------------------------------------------------------------------------------------
USTRUCT() struct TLGAME_API FSTE_TLG_GetPlayerController_InstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Output") TObjectPtr<ATLG_Player_Controller> TLG_Player_Controller = 0;  // Binded in editor
};
//------------------------------------------------------------------------------------------------------------
USTRUCT() struct  TLGAME_API FTLG_STE_Core_Enemy : public FStateTreeEvaluatorBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTE_TLG_GetPlayerController_InstanceData;  // Override FInstanceDataType in parant
	virtual void TreeStart(FStateTreeExecutionContext &context) const;
	
	virtual const UStruct *GetInstanceDataType() const;
};
//------------------------------------------------------------------------------------------------------------
