//------------------------------------------------------------------------------------------------------------
#include <GBG_Player.h>
#include <GBG_Player_Controller.h>
#include <EnhancedInputComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Player
AGBG_Player::AGBG_Player()
{
	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(Action_Move, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Look, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Jump, TEXT("Please insert something in BP") );
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);

	if (UEnhancedInputComponent *enhanced_input_component = Cast<UEnhancedInputComponent>(player_input_component))
	{
		enhanced_input_component->BindAction(Action_Move, ETriggerEvent::Triggered, this, &AGBG_Player::Move);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		enhanced_input_component->BindAction(Action_Look, ETriggerEvent::Triggered, this, &AGBG_Player::Look);
	}
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGBG_Player::GetAbilitySystemComponent() const
{
	return 0;
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::Move(const FInputActionValue &value)
{
	FVector2D movement_vector = value.Get<FVector2D>();
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yaw_rotation(0, rotation.Yaw, 0);
	const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
	const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

	if (Controller == 0)
		return;

	AddMovementInput(forward_direction , movement_vector.Y);
	AddMovementInput(right_direction , movement_vector.X);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::Look(const FInputActionValue &value)
{
	FVector2D look_axis_vector = value.Get<FVector2D>();

	if (Controller == 0)
		return;
	
	AddControllerYawInput(look_axis_vector.X);
	AddControllerPitchInput(look_axis_vector .Y);
}
//------------------------------------------------------------------------------------------------------------
