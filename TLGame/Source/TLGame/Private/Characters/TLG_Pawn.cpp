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
void ATLG_Pawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//------------------------------------------------------------------------------------------------------------
void ATLG_Pawn::PossessedBy(AController *new_controller)
{
	Super::PossessedBy(new_controller);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Pawn::GetAbilitySystemComponent() const
{
	if (Ability_System_Component != 0)
		return Ability_System_Component;

	ATLG_Player_State* ps = GetPlayerState<ATLG_Player_State>();
	if (ps == 0)
		return 0;

	Ability_System_Component = ps->GetAbilitySystemComponent();

	return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
