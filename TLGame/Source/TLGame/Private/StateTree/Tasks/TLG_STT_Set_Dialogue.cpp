//------------------------------------------------------------------------------------------------------------
#include <StateTree/Tasks/TLG_STT_Set_Dialogue.h>

#include <Subsystems/TLG_Subsystem_Story.h>
#include <Components/TLG_Component_Dialogue.h>

#include <StateTreeExecutionContext.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STT_Set_Dialogue
EStateTreeRunStatus UTLG_STT_Set_Dialogue::EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition)
{
    UGameInstance *game_instance;
	UTLG_Subsystem_Story *tlg_subsystem_story;
	
	if (TLG_Component_Dialogue == 0)
		return EStateTreeRunStatus::Failed;

	TLG_Component_Dialogue->Set_Dialogue_Current(Dialogue_Table);
	TLG_Component_Dialogue->On_Dialogue_Ended.AddUObject(this, &UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended);

	game_instance = context.GetWorld()->GetGameInstance();
	if (game_instance != 0)
	{
		tlg_subsystem_story = game_instance->GetSubsystem<UTLG_Subsystem_Story>();
		tlg_subsystem_story->Add_Story_Flag(Story_Flag_To_Add);
	}

	return EStateTreeRunStatus::Running;  // I`m still working, wait
}
//------------------------------------------------------------------------------------------------------------
void UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended()
{
	TLG_Component_Dialogue->On_Dialogue_Ended.RemoveAll(this);

	FinishTask();
}
//------------------------------------------------------------------------------------------------------------
