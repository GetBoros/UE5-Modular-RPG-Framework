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
		
	UFUNCTION(BlueprintCallable) void PerformInteractionTrace(FHitResult &HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction") float TraceDistance = 5000.0f;
};
