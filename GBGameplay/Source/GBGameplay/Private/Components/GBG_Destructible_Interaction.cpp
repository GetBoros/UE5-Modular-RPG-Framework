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
void UGBG_Destructible_Interaction::PerformInteractionTrace(FHitResult &HitResult)
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

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(MyOwner); // ВАЖНО: Игнорируем самого игрока, чтобы луч не попал в него

	bool bHit = World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams);
	DrawDebugLine(World, StartTrace, EndTrace, bHit ? FColor::Green : FColor::Red, false, 5.0f, 0, 1.0f);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
			UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *HitActor->GetName());
	}
}
//------------------------------------------------------------------------------------------------------------
