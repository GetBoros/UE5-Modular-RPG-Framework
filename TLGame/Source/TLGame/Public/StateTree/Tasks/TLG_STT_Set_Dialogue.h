//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/StateTreeTaskBlueprintBase.h>

#include <TLG_STT_Set_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_Player_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_STT_Set_Dialogue : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition);
	
private:
	void Handle_Dialogue_Ended();

	UPROPERTY(EditAnywhere, Category = "Condition") FGameplayTag Story_Flag_To_Add;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<ATLG_Player_Controller> TLG_Player_Controller;
	UPROPERTY(EditAnywhere) TObjectPtr<UDataTable> Dialogue_Table;

};
//------------------------------------------------------------------------------------------------------------
