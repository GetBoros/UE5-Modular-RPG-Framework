//------------------------------------------------------------------------------------------------------------
#include <StateTree/Evaluators/TLG_STE_Core_Enemy.h>
#include <System/TLG_Player_Controller.h>
#include <StateTreeExecutionContext.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STE_Core_Enemy
void UTLG_STE_Core_Enemy::TreeStart(FStateTreeExecutionContext &context)
{
	Super::TreeStart(context);

	TLG_Player_Controller = Cast<ATLG_Player_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0) );

}
//------------------------------------------------------------------------------------------------------------
