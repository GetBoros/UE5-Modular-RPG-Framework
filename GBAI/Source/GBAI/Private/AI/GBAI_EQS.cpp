//------------------------------------------------------------------------------------------------------------
#include "AI/GBAI_EQS.h"
#include "Interfaces/GBC_AI_Queryable_Interface.h"
#include "GameplayTagAssetInterface.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
//------------------------------------------------------------------------------------------------------------




// UGBAI_EQS
UGBAI_EQS::UGBAI_EQS()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();

	TestPurpose = EEnvTestPurpose::Score;
}
//------------------------------------------------------------------------------------------------------------
void UGBAI_EQS::RunTest(FEnvQueryInstance &query_instance) const
{
    float queried_value;
    AActor *item_actor;
    
    UObject *query_owner = query_instance.Owner.Get();
    if (query_owner == 0)
        return;
    
    Score_Multiplier.BindData(query_owner, query_instance.QueryID);
    const float multiplier_value = Score_Multiplier.GetValue();

    for (FEnvQueryInstance::ItemIterator it(this, query_instance); it; ++it)
    {
        item_actor = GetItemActor(query_instance, it.GetIndex() );
        if (item_actor == 0)
        {
            it.ForceItemState(EEnvItemStatus::Failed);
            continue;
        }

        if (IGBC_AI_Queryable_Interface::Execute_Query_Float_Value_By_Tag(item_actor, Tag_Data_To_Query, queried_value) )   // «апрашиваем значение по тегу, который задан в редакторе
        {// CHANGE: »спользуем встроенные в тест параметры дл€ min/max

            const float final_score = queried_value * multiplier_value;
            
            it.SetScore(TestPurpose, FilterType, final_score, BoolValue.GetValue(), BoolValue.GetValue() );
        }
        else
            it.ForceItemState(EEnvItemStatus::Failed);  // »нтерфейс есть, но на наш конкретный тег он ответить не смог
    }
}
//------------------------------------------------------------------------------------------------------------
FText UGBAI_EQS::GetDescriptionTitle() const
{
	return FText::FromString(TEXT("Score by Nutrition"));
}
//------------------------------------------------------------------------------------------------------------
FText UGBAI_EQS::GetDescriptionDetails() const
{
	return FText::FromString(TEXT("Higher Nutrition = Better Score"));
}
//------------------------------------------------------------------------------------------------------------
