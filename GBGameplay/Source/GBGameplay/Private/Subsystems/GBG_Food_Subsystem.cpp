//------------------------------------------------------------------------------------------------------------
#include "Subsystems/GBG_Food_Subsystem.h"
//------------------------------------------------------------------------------------------------------------




// UGBG_Food_Subsystem
void UGBG_Food_Subsystem::Register(AActor *actor)
{
    if (actor != 0 && Registred_Actors.Contains(actor) == false)
        Registred_Actors.Add(actor);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Food_Subsystem::Unregister(AActor *actor)
{
    if (actor != 0)
        Registred_Actors.Remove(actor);
}
//------------------------------------------------------------------------------------------------------------
AActor *UGBG_Food_Subsystem::Get_Closest_Food(const FVector &location) const
{
    float min_distance_sq = FLT_MAX;  // Max value in float
    AActor *closest_actor = 0;

    for (AActor *food_actor : Registred_Actors)
    {
        if (IsValid(food_actor) != true)
            continue;  // if actor not valid, destroyed but not unsub

        const float dist_sq = FVector::DistSquared(location, food_actor->GetActorLocation() );  // It`s faster

        if (dist_sq < min_distance_sq)
        {
            min_distance_sq = dist_sq;
            closest_actor = food_actor;
        }
    }
    return closest_actor;
}
//------------------------------------------------------------------------------------------------------------
