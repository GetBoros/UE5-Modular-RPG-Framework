//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Subsystems/WorldSubsystem.h"
#include "GBG_Food_Subsystem.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_Food_Subsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    void Register(AActor *actor);
    void Unregister(AActor *actor);

    UFUNCTION(BlueprintCallable, Category = "AI|Food") AActor *Get_Closest_Food(const FVector &location) const;  // Find closest actor (optimized without GetAllActorsOfClass
    
    UPROPERTY() TArray<AActor *> Registred_Actors;  // Stored all actor. Use TWeakObjectPtr if need to not get crash, (safety first)
};
//------------------------------------------------------------------------------------------------------------
