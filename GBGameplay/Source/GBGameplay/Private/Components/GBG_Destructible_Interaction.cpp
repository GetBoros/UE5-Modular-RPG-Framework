//------------------------------------------------------------------------------------------------------------
#include <Components/GBG_Destructible_Interaction.h>
#include <Kismet/GameplayStatics.h>
#include <Camera/PlayerCameraManager.h>
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
//------------------------------------------------------------------------------------------------------------




// UGBG_Destructible_Interaction
UGBG_Destructible_Interaction::UGBG_Destructible_Interaction()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(Actor_Class_To_Spawn, TEXT("Hello world") );
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function)
{
	Super::TickComponent(delta_time, tick_type, this_tick_function);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::Perform_Interaction_Trace(AActor *&result)
{
	bool is_hit;
	FHitResult hit_result;
	FCollisionQueryParams collision_params;
	FVector spawn_location;
	FRotator spawn_rotation;

	AActor *hit_actor, *new_actor, *owner;
	APawn *instigator;
	UWorld *world;
	APlayerCameraManager *camera_manager;

	owner = GetOwner();
	if (owner == 0)
		return;

	world = GetWorld();
	if (world == 0)
		return;

	camera_manager = UGameplayStatics::GetPlayerCameraManager(world, 0);
	if (camera_manager == 0)
		return;

	const FVector forward_vector = camera_manager->GetCameraRotation().Vector();
	const FVector start_trace = camera_manager->GetCameraLocation();
	const FVector end_trace = start_trace + (forward_vector * Trace_Distance);

	collision_params.AddIgnoredActor(owner);
	is_hit = world->LineTraceSingleByChannel(hit_result, start_trace, end_trace, ECC_Visibility, collision_params);
	DrawDebugLine(world, start_trace, end_trace, is_hit ? FColor::Green : FColor::Red, false, 5.0f, 0, 1.0f);

	if (is_hit == false)
		return;
	
	hit_actor = hit_result.GetActor();
	if (hit_actor == 0)
		return;

	if (hit_result.GetComponent()->ComponentHasTag(TEXT("Temp")) != true)
		return;
	UE_LOG(LogTemp, Log, TEXT("Trace hit valid component on actor: %s"), *hit_result.GetActor()->GetName() );
	
	if (Actor_Class_To_Spawn == 0)
		return;

	spawn_location = hit_result.Location;
	spawn_rotation = FRotator::ZeroRotator;
	instigator = Cast<APawn>(owner);
	
	const FTransform spawn_transform(spawn_rotation, spawn_location);
	new_actor = world->SpawnActorDeferred<AActor>(Actor_Class_To_Spawn, spawn_transform, owner, 0, Spawn_Collision_Method);
	new_actor->SetLifeSpan(2.0f);  // 0.2f to short times
	UGameplayStatics::FinishSpawningActor(new_actor, spawn_transform);
	result = new_actor;
}
//------------------------------------------------------------------------------------------------------------
