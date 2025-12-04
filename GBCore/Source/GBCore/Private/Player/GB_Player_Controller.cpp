//------------------------------------------------------------------------------------------------------------
#include "Player/GB_Player_Controller.h"
//------------------------------------------------------------------------------------------------------------
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/GB_Character_Interface.h"
//------------------------------------------------------------------------------------------------------------




// AGB_Player_Controller
AGB_Player_Controller::AGB_Player_Controller()
{

}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Controller::BeginPlay()
{
	ULocalPlayer *player;
	UEnhancedInputLocalPlayerSubsystem *input_subsystem;

	Super::BeginPlay();

	player = Cast<ULocalPlayer>(Player);
	if (player == 0)
		return;

	input_subsystem = player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (input_subsystem == 0)
		return;

	input_subsystem->AddMappingContext(Input_Mapping_Context, 0);
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Controller::SetupInputComponent()
{
	UEnhancedInputComponent *enhanced_input_component;

	Super::SetupInputComponent();

	enhanced_input_component = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (enhanced_input_component == 0)
		return;

	enhanced_input_component->BindAction(Move_Action, ETriggerEvent::Triggered, this, &AGB_Player_Controller::Handle_Move);
	enhanced_input_component->BindAction(Move_Action, ETriggerEvent::Completed, this, &AGB_Player_Controller::Handle_Move_Completed);
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Controller::Handle_Move(const FInputActionValue& input_action_value)
{
	const FVector2D movement_vector = input_action_value.Get<FVector2D>();
	IGB_Character_Interface *character_interface;
	APawn* controlled_pawn;
	
	controlled_pawn = GetPawn();
	if (controlled_pawn == 0)
		return;

	character_interface = Cast<IGB_Character_Interface>(controlled_pawn);
	if (character_interface != 0)
		character_interface->Execute_Move(controlled_pawn, FVector2D(movement_vector.Y, movement_vector.X), 1.0f);
}
//------------------------------------------------------------------------------------------------------------
void AGB_Player_Controller::Handle_Move_Completed(const FInputActionValue& input_action_value)
{
	IGB_Character_Interface *character_interface;
	APawn *controlled_pawn;

	controlled_pawn = GetPawn();
	if (controlled_pawn != 0)
		return;

	character_interface = Cast<IGB_Character_Interface>(controlled_pawn);
	if (character_interface != 0)
		character_interface->Execute_Move(controlled_pawn, FVector2D::ZeroVector, 0.0f);

}
//------------------------------------------------------------------------------------------------------------
