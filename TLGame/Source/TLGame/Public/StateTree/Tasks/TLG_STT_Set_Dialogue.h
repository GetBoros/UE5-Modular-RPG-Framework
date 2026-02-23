//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/StateTreeTaskBlueprintBase.h>

#include <TLG_STT_Set_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_STT_Set_Dialogue : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition);
	
	UFUNCTION() void Handle_Dialogue_Ended();

	UPROPERTY(EditAnywhere) TObjectPtr<UDataTable> Dialogue_Table;
};
//------------------------------------------------------------------------------------------------------------
