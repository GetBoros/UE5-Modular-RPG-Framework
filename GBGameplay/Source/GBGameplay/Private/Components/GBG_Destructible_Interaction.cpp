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
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function)
{
	Super::TickComponent(delta_time, tick_type, this_tick_function);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Destructible_Interaction::PerformInteractionTrace(bool &is_actor_with_tag, FTransform &transform)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
		return; // Если владельца нет, выходим

	UWorld* World = GetWorld();
	if (!World)
		return; // Если мира нет, выходим

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0);
	if (!CameraManager)
		return;

	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FVector ForwardVector = CameraManager->GetCameraRotation().Vector(); // Получаем вектор направления из ротации камеры
	const FVector StartTrace = CameraLocation;
	const FVector EndTrace = StartTrace + (ForwardVector * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(MyOwner);

	bool bHit = World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams);
	DrawDebugLine(World, StartTrace, EndTrace, bHit ? FColor::Green : FColor::Red, false, 5.0f, 0, 1.0f);

	if (bHit == false)
		return;
	AActor* HitActor = HitResult.GetActor();
	if (HitActor)
		UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *HitActor->GetName());

	if (HitResult.GetComponent()->ComponentHasTag(TEXT("Temp") ) )
	{
		// Spawn Actor | Make Transform | Set Class | 

		// For spawn actor set Activation type triger

		is_actor_with_tag = true;
		transform.SetLocation(HitResult.Location);
	}
}
//------------------------------------------------------------------------------------------------------------
