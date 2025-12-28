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
	Tag_Destructible = TEXT("Temp");
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
void UGBG_Destructible_Interaction::Interact()
{
	FHitResult hit_result;

	Find_Target_Under_Reticle(hit_result);
	Try_Spawn_Destructible(hit_result);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::Find_Target_Under_Reticle(FHitResult &hit_result) const
{
	const APlayerCameraManager *camera_manager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (camera_manager == 0)
		return;
	const FVector forward_vector = camera_manager->GetCameraRotation().Vector();
	const FVector start_trace = camera_manager->GetCameraLocation();
	const FVector end_trace = start_trace + (forward_vector * Trace_Distance);

	if (GetWorld()->LineTraceSingleByChannel(hit_result, start_trace, end_trace, ECC_Visibility, FCollisionQueryParams(SCENE_QUERY_STAT(MyTrace), false, GetOwner() ) ) )
		DrawDebugLine(GetWorld(), start_trace, end_trace, FColor::Green, false, 5.0f, 0, 1.0f);
	else
		DrawDebugLine(GetWorld(), start_trace, end_trace, FColor::Red, false, 5.0f, 0, 1.0f);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::Try_Spawn_Destructible(const FHitResult &hit_result)
{
	AActor *actor_to_spawn;

	if (hit_result.GetComponent()->ComponentHasTag(Tag_Destructible) != true)
		return;

	const FTransform spawn_transform(FRotator::ZeroRotator, hit_result.Location);
	actor_to_spawn = GetWorld()->SpawnActorDeferred<AActor>(Actor_Class_To_Spawn, spawn_transform, Cast<APawn>(GetOwner() ), 0, Spawn_Collision_Method);
	UGameplayStatics::FinishSpawningActor(actor_to_spawn, spawn_transform);
	actor_to_spawn->SetLifeSpan(2.0f);  // If FS_MasterField start destroy after 1 sec need destroy object after 2 seconds
}
//------------------------------------------------------------------------------------------------------------
