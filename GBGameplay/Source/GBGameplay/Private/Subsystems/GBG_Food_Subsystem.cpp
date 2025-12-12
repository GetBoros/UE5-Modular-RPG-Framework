//------------------------------------------------------------------------------------------------------------
#include "Subsystems/GBG_Food_Subsystem.h"
//------------------------------------------------------------------------------------------------------------




// UGBG_Food_Subsystem
void UGBG_Food_Subsystem::Register_Food(AActor *food_actor)
{
    if (food_actor && !All_Food_On_Level.Contains(food_actor) )
        All_Food_On_Level.Add(food_actor);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Food_Subsystem::Unregister_Food(AActor *food_actor)
{
    if (food_actor)
        All_Food_On_Level.Remove(food_actor);
}
//------------------------------------------------------------------------------------------------------------
AActor *UGBG_Food_Subsystem::Get_Closest_Food(const FVector &location) const
{
    float min_distance_sq = FLT_MAX;  // Максимально возможное число
    AActor *closest_actor = nullptr;

    for (AActor *food_actor : All_Food_On_Level)
    {
        if (!IsValid(food_actor) )  // Проверка на валидность (на случай если актор уничтожен, но не отписался)
            continue;

        const float dist_sq = FVector::DistSquared(location, food_actor->GetActorLocation() );  // Считаем дистанцию в квадрате (это быстрее, чем обычная дистанция с корнем)

        if (dist_sq < min_distance_sq)
        {
            min_distance_sq = dist_sq;
            closest_actor = food_actor;
        }
    }

    return closest_actor;
}
//------------------------------------------------------------------------------------------------------------
