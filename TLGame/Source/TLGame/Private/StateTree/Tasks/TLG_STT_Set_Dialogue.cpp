//------------------------------------------------------------------------------------------------------------
#include <StateTree/Tasks/TLG_STT_Set_Dialogue.h>

#include <System/TLG_Player_Controller.h>
#include <StateTreeExecutionContext.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STT_Set_Dialogue
EStateTreeRunStatus UTLG_STT_Set_Dialogue::EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition)
{
	AActor *test;

	TLG_Player_Controller = Cast<ATLG_Player_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0) );
	if (TLG_Player_Controller == 0)
		return EStateTreeRunStatus::Failed;

	test = Cast<AActor>(context.GetOwner());

	// TODO TLG_Player_Controller Set DT And bind on delegate

	return EStateTreeRunStatus::Running;  // I`m still working, wait
}
//------------------------------------------------------------------------------------------------------------
void UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended()
{
	//if (TLG_Player_Controller)
	//	TLG_Player_Controller->On_Dialogue_Ended.RemoveDynamic(this, &UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended);

	FinishTask();
}
//------------------------------------------------------------------------------------------------------------
