//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/ActorComponent.h>
#include <GBG_Destructible_Interaction.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class GBGAMEPLAY_API UGBG_Destructible_Interaction : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGBG_Destructible_Interaction();
	
	virtual void BeginPlay();
	virtual void TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function);
		
	UFUNCTION(BlueprintCallable) void Perform_Interaction_Trace(AActor *&result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction") float Trace_Distance = 5000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Spawning") TSubclassOf<AActor> Actor_Class_To_Spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Spawning") ESpawnActorCollisionHandlingMethod Spawn_Collision_Method = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
};
