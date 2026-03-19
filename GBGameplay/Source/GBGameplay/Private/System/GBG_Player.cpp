//------------------------------------------------------------------------------------------------------------
#include <System/GBG_Player.h>
#include <System/GBG_Player_State.h>

#include <Components/GBG_Destructible_Interaction.h>

#include <EnhancedInputComponent.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Player
AGBG_Player::AGBG_Player()
{
	PrimaryActorTick.bCanEverTick = false;

	Destructible_Interaction_Component = CreateDefaultSubobject<UGBG_Destructible_Interaction>(TEXT("DestructibleInteractionComponent") );  // !!! TEMP
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(Action_Move, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Look, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Jump, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Sprint, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Interact, TEXT("Please insert something in BP") );
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::PossessedBy(AController *new_controller)
{
	Super::PossessedBy(new_controller);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	UEnhancedInputComponent *enhanced_input_component;

	Super::SetupPlayerInputComponent(player_input_component);

	enhanced_input_component = Cast<UEnhancedInputComponent>(player_input_component);
	if (enhanced_input_component != 0)
	{
		enhanced_input_component->BindAction(Action_Move, ETriggerEvent::Triggered, this, &AGBG_Player::On_Move);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Started, this, &AGBG_Player::On_Jump_Bgn);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Completed, this, &AGBG_Player::On_Jump_End);
		enhanced_input_component->BindAction(Action_Look, ETriggerEvent::Triggered, this, &AGBG_Player::On_Look);
		enhanced_input_component->BindAction(Action_Sprint, ETriggerEvent::Started, this, &AGBG_Player::On_Sprint_Bgn);
		enhanced_input_component->BindAction(Action_Sprint, ETriggerEvent::Completed, this, &AGBG_Player::On_Sprint_End);
		enhanced_input_component->BindAction(Action_Interact, ETriggerEvent::Started, this, &AGBG_Player::On_Interact);
	}
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *AGBG_Player::GetAbilitySystemComponent() const
{
	AGBG_Player_State *tlg_player_state;

	if (Ability_System_Component != 0)
		return Ability_System_Component;

	tlg_player_state = GetPlayerState<AGBG_Player_State>();
	if (tlg_player_state == 0)
		return 0;

	Ability_System_Component = tlg_player_state->GetAbilitySystemComponent();

	return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Move(const FInputActionValue &value)
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
void AGBG_Player::On_Look(const FInputActionValue &value)
{
	FVector2D look_axis_vector = value.Get<FVector2D>();

	if (Controller == 0)
		return;
	
	AddControllerYawInput(look_axis_vector.X);
	AddControllerPitchInput(look_axis_vector.Y);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Jump_Bgn(const FInputActionValue &value)
{
	Jump();
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Jump_End(const FInputActionValue &value)
{
	StopJumping();
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Sprint_Bgn(const FInputActionValue &value)
{
	constexpr int32 sprint_input_id = 1;  // !!! TEMP Magic number || Can receive ID from Input Action

	if (Ability_System_Component == 0)
		return;
	Ability_System_Component->AbilityLocalInputPressed(sprint_input_id);  // Ability_System_Component know what input id is a sprint so use it
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Sprint_End(const FInputActionValue &value)
{
	constexpr int32 sprint_input_id = 1;  // !!! TEMP Magic number || Can receive ID from Input Action

	if (Ability_System_Component == 0)
		return;
	Ability_System_Component->AbilityLocalInputReleased(sprint_input_id);  // Ability_System_Component know what input id is a sprint so use it
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::On_Interact(const FInputActionValue& value)
{
	Destructible_Interaction_Component->Interact();
}
//------------------------------------------------------------------------------------------------------------
