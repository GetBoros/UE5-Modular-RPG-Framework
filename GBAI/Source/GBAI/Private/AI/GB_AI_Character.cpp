//------------------------------------------------------------------------------------------------------------
#include "AI/GB_AI_Character.h"
#include "AI/GB_AI_Controller.h"
//------------------------------------------------------------------------------------------------------------




// AGB_AI_Character
AGB_AI_Character::AGB_AI_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AGB_AI_Controller::StaticClass();
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
void AGB_AI_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
