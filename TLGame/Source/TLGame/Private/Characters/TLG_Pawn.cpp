//------------------------------------------------------------------------------------------------------------
#include <Characters/TLG_Pawn.h>
#include <System/TLG_Player_State.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Pawn
ATLG_Pawn::ATLG_Pawn()
{
	PrimaryActorTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//------------------------------------------------------------------------------------------------------------
void ATLG_Pawn::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Pawn::PossessedBy(AController *new_controller)
{
	Super::PossessedBy(new_controller);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Pawn::GetAbilitySystemComponent() const
{
	ATLG_Player_State *tlg_player_state;

	if (Ability_System_Component != 0)
		return Ability_System_Component;

	tlg_player_state = GetPlayerState<ATLG_Player_State>();
	if (tlg_player_state == 0)
		return 0;

	Ability_System_Component = tlg_player_state->GetAbilitySystemComponent();

	return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
