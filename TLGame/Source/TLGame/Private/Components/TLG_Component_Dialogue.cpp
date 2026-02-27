//------------------------------------------------------------------------------------------------------------
#include <Components/TLG_Component_Dialogue.h>
//------------------------------------------------------------------------------------------------------------





// UTLG_Component_Dialogue
UTLG_Component_Dialogue::UTLG_Component_Dialogue()
{
	PrimaryComponentTick.bCanEverTick = false;

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::BeginPlay()
{
	Super::BeginPlay();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function)
{
	Super::TickComponent(delta_time, tick_type, this_tick_function);

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Dialogue_Start(const FName &row_id)
{

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Dialogue_End()
{

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Dialogue::Handle_Player_Decision(const FPlayer_Response &player_response)
{

}
//------------------------------------------------------------------------------------------------------------

