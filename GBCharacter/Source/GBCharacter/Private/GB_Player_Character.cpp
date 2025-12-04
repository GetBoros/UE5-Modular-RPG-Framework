//------------------------------------------------------------------------------------------------------------
#include "GB_Player_Character.h"
//------------------------------------------------------------------------------------------------------------
AGB_Player_Character::AGB_Player_Character()
{
	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Character::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Character::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Character::Move_Implementation(const FVector2D &world_direction, float scale_value)
{
	if (Controller == 0 || scale_value == 0.0f)
		return;

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yaw_rotation(0, rotation.Yaw, 0);

	const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
	const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forward_direction, world_direction.X * scale_value);
	AddMovementInput(right_direction, world_direction.Y * scale_value);
}
//------------------------------------------------------------------------------------------------------------
FGB_Types_Health AGB_Player_Character::Get_Types_Health_Implementation()
{
	return FGB_Types_Health
	{
		.Health_Current = Health_Current,
		.Health_Max = Health_Max
	};
}
//------------------------------------------------------------------------------------------------------------
FVector AGB_Player_Character::Get_Target_Location_Implementation()
{
	return FVector();
}
//------------------------------------------------------------------------------------------------------------

