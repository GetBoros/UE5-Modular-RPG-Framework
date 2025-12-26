//------------------------------------------------------------------------------------------------------------
#include <GBG_Player.h>

#include <GAS/GBG_Gameplay_Ability.h>
#include <GAS/GBG_Attribute_Set.h>

#include <EnhancedInputComponent.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Player
AGBG_Player::AGBG_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	Ability_System_Component = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent") );
	Ability_System_Component->SetIsReplicated(true);
	Ability_System_Component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);  // Mixed standart for Character

	Attribute_Set = CreateDefaultSubobject<UGBG_Attribute_Set>(TEXT("AttributeSet") );
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(Action_Move, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Look, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Jump, TEXT("Please insert something in BP") );
	ensureMsgf(Action_Sprint, TEXT("Please insert something in BP") );
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

	if (Ability_System_Component == 0)
		return;
	Ability_System_Component->InitAbilityActorInfo(this, this);

	if (Default_Attributes_Effect == 0)  // Apply Game Effect for set up starting attributes
		return;

	FGameplayEffectContextHandle effect_context = Ability_System_Component->MakeEffectContext();  // Create handle
	effect_context.AddSourceObject(this);  // add handle
	FGameplayEffectSpecHandle spec_handle = Ability_System_Component->MakeOutgoingSpec(Default_Attributes_Effect, 1, effect_context);
	
	if (spec_handle.IsValid() == true)
		Ability_System_Component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get() );  // Apply effect to self

	for (const auto ability_class : Default_Abilities)  // Learn abilities by default
	{
		if (ability_class == 0)
			continue;

		const UGBG_Gameplay_Ability *ability_cdo = ability_class->GetDefaultObject<UGBG_Gameplay_Ability>();  // Get Input id from ability template
		
		int32 input_id = ability_cdo ? ability_cdo->Input_ID : 0;  // Get Input id or set 0
		FGameplayAbilitySpec ability_spec(ability_class, 1, input_id, this);

		Ability_System_Component->GiveAbility(ability_spec);  // Give ability to player
	}
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);

	if (UEnhancedInputComponent *enhanced_input_component = Cast<UEnhancedInputComponent>(player_input_component) )
	{
		enhanced_input_component->BindAction(Action_Move, ETriggerEvent::Triggered, this, &AGBG_Player::Move);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Started, this, &AGBG_Player::On_Jump_Bgn);
		enhanced_input_component->BindAction(Action_Jump, ETriggerEvent::Completed, this, &AGBG_Player::On_Jump_End);
		enhanced_input_component->BindAction(Action_Look, ETriggerEvent::Triggered, this, &AGBG_Player::Look);
		enhanced_input_component->BindAction(Action_Sprint, ETriggerEvent::Started, this, &AGBG_Player::On_Sprint_Bgn);
		enhanced_input_component->BindAction(Action_Sprint, ETriggerEvent::Completed, this, &AGBG_Player::On_Sprint_End);
	}
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *AGBG_Player::GetAbilitySystemComponent() const
{
	return Ability_System_Component;
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
