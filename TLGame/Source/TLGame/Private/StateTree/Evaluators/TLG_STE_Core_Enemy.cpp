//------------------------------------------------------------------------------------------------------------
#include <StateTree/Evaluators/TLG_STE_Core_Enemy.h>
#include <System/TLG_Player_Controller.h>

#include <StateTreeExecutionContext.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// FTLG_STE_Core_Enemy
void FTLG_STE_Core_Enemy::TreeStart(FStateTreeExecutionContext &context) const
{
	FInstanceDataType &instance_data_type = context.GetInstanceData(*this);

	if (UWorld *world = context.GetWorld() )
		instance_data_type.TLG_Player_Controller = Cast<ATLG_Player_Controller>(UGameplayStatics::GetPlayerController(world, 0) );
}
//------------------------------------------------------------------------------------------------------------
const UStruct *FTLG_STE_Core_Enemy::GetInstanceDataType() const
{
	return FInstanceDataType::StaticStruct();
}
//------------------------------------------------------------------------------------------------------------
