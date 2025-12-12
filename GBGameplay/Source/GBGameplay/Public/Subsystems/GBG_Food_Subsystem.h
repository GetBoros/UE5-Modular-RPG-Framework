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
    void Register_Food(AActor *food_actor);
    void Unregister_Food(AActor *food_actor);

    UFUNCTION(BlueprintCallable, Category = "AI|Food") AActor *Get_Closest_Food(const FVector &location) const;  // Поиск ближайшей еды (оптимизированный, без GetAllActorsOfClass)
    
    UPROPERTY() TArray<AActor *> All_Food_On_Level;  // Храним список всей еды. Используем TWeakObjectPtr, чтобы не крашнуться, если актор удалят мимо нас (safety first).
};
//------------------------------------------------------------------------------------------------------------
