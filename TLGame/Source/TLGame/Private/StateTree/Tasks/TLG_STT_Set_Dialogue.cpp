//------------------------------------------------------------------------------------------------------------
#include <StateTree/Tasks/TLG_STT_Set_Dialogue.h>

#include <System/TLG_Player_Controller.h>
#include <StateTreeExecutionContext.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STT_Set_Dialogue
EStateTreeRunStatus UTLG_STT_Set_Dialogue::EnterState(FStateTreeExecutionContext &context, const FStateTreeTransitionResult &transition)
{
	ATLG_Player_Controller *test;

	test = Cast<ATLG_Player_Controller>(context.GetOwner() );

	if (test != 0)
	{
		int yy = 0;

		yy++;
	}

	if (TLG_Player_Controller != 0)
	{
		int yy = 0;

		yy++;
	}

	TLG_Player_Controller = Cast<ATLG_Player_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0) );
	
	if (TLG_Player_Controller != 0)
	{
		int yy = 0;

		yy++;
		// 2. Подписываемся на делегат завершения диалога
		// TLG_Player_Controller->On_Dialogue_Ended.AddDynamic(this, &UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended);

		// 3. Запускаем UI и передаем таблицу
		// TLG_Player_Controller->Start_Encounter(Dialogue_Table);

		// 4. Говорим дереву: "Я работаю, жди"
		return EStateTreeRunStatus::Running;
	}

	return EStateTreeRunStatus::Failed;
	
	// return EStateTreeRunStatus::Running;  // I`m still working, wait
	// return EStateTreeRunStatus::Succeeded;  // I`m done working
}
//------------------------------------------------------------------------------------------------------------
void UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended()
{
	//if (TLG_Player_Controller)
	//	TLG_Player_Controller->On_Dialogue_Ended.RemoveDynamic(this, &UTLG_STT_Set_Dialogue::Handle_Dialogue_Ended);

	FinishTask();
}
//------------------------------------------------------------------------------------------------------------
