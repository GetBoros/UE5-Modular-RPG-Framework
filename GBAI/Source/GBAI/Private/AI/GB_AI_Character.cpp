//------------------------------------------------------------------------------------------------------------
#include <AI/GB_AI_Character.h>
#include <AI/GB_AI_Controller.h>

//------------------------------------------------------------------------------------------------------------




// AGB_AI_Character
AGB_AI_Character::AGB_AI_Character()
 : AI_Controller(0)
{
	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	//AI_Stat_Component->On_Changed_Stamina.RemoveDynamic(this, &AGB_AI_Character::On_Stamina_Changed);

	Super::EndPlay(end_play_reason);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	AI_Controller = Cast<AGB_AI_Controller>(controller);
	//if (IsValid(AI_Controller) == true)
	//	AI_Controller->On_AI_Action_Requested.AddDynamic(this, &AGB_AI_Character::Handle_On_AI_Action_Requested);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::UnPossessed()
{
	if (AI_Controller != 0)
	//	AI_Controller->On_AI_Action_Requested.RemoveDynamic(this, &AGB_AI_Character::Handle_On_AI_Action_Requested);
	//AI_Controller = 0;

	Super::UnPossessed();
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::SetupPlayerInputComponent(UInputComponent* player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//AI_Stat_Component->On_Changed_Stamina.AddDynamic(this, &AGB_AI_Character::On_Stamina_Changed);  // !!! TEMP
}
//------------------------------------------------------------------------------------------------------------
FGenericTeamId AGB_AI_Character::GetGenericTeamId() const
{
	return ETeamAttitude::Friendly;
}
//------------------------------------------------------------------------------------------------------------
