#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GB_RegenComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UGB_RegenComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGB_RegenComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
