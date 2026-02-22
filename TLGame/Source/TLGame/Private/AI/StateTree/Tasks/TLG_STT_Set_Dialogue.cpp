//------------------------------------------------------------------------------------------------------------
#include <AI/StateTree/Tasks/TLG_STT_Set_Dialogue.h>
//------------------------------------------------------------------------------------------------------------

EStateTreeRunStatus UTLG_STT_Set_Dialogue::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{

	return EStateTreeRunStatus::Running;
}

void UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended()
{
}
