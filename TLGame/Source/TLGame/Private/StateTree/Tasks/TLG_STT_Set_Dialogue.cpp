//------------------------------------------------------------------------------------------------------------
#include <StateTree/Tasks/TLG_STT_Set_Dialogue.h>

#include <System/TLG_Player_Controller.h>
#include <StateTreeExecutionContext.h>

//------------------------------------------------------------------------------------------------------------




// UTLG_STT_Set_Dialogue
EStateTreeRunStatus UTLG_STT_Set_Dialogue::EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition)
{
    context.GetOwner();
    // tlg_player_controller->On_Dialogue_Ended.AddDynamic(this, &FTLG_Task_PlayDialogue::Handle_Dialogue_Ended);

    
    //tlg_player_controller->Start_Encounter(Dialogue_Table);  // Запускаем UI

	return EStateTreeRunStatus::Running;  // I`m still working, wait
	// return EStateTreeRunStatus::Succeeded;  // I`m done working
}
//------------------------------------------------------------------------------------------------------------
void UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended()
{
    // Диалог окончен. Говорим дереву, что задача выполнена успешно.
        // (В C++ это делается через отправку события в StateTreeExecutionContext)
}
//------------------------------------------------------------------------------------------------------------
