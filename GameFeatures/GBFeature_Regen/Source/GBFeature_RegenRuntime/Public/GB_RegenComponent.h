//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/ActorComponent.h>
#include <GB_RegenComponent.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class UGB_RegenComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGB_RegenComponent();

    virtual void TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function);
};
//------------------------------------------------------------------------------------------------------------
