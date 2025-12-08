//------------------------------------------------------------------------------------------------------------
#include "AI/GB_AI_EQS.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
//------------------------------------------------------------------------------------------------------------




// UGB_AI_EQS
UGB_AI_EQS::UGB_AI_EQS()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();

	// ВАЖНО: Этот тест предназначен для ОЦЕНКИ (Score), а не фильтрации по умолчанию
	TestPurpose = EEnvTestPurpose::Score;
}
//------------------------------------------------------------------------------------------------------------
void UGB_AI_EQS::RunTest(FEnvQueryInstance& QueryInstance) const
{
//	UObject *query_owner = QueryInstance.Owner.Get();
//	AActor *querier = Cast<AActor>(query_owner);
//	AActor *item_actor;
//	AGB_AI_Actor *item_food;
//	AGB_AI_Character *character = Cast<AGB_AI_Character>(querier);
//
//	FloatValueMin.BindData(query_owner, QueryInstance.QueryID);
//	FloatValueMax.BindData(query_owner, QueryInstance.QueryID);
//	
//	float threshold_min = FloatValueMin.GetValue();
//	float threshold_max = FloatValueMax.GetValue();
//	float HungerFactor = 1.0f;
//	
//	if (character != 0)
//		if (character->Get_Hunger() < 20.0f)
//			HungerFactor = 5.0f;
//
//	for (FEnvQueryInstance::ItemIterator it(this, QueryInstance); it; ++it)
//	{
//		item_actor = GetItemActor(QueryInstance, it.GetIndex());
//		item_food = Cast<AGB_AI_Actor>(item_actor);
//
//		if (item_food != 0)
//		{
//			float final_score = item_food->NutritionValue * HungerFactor;
//
//			it.SetScore(TestPurpose, FilterType, final_score, threshold_min, threshold_max);
//		}
//		else
//			it.ForceItemState(EEnvItemStatus::Failed);
//	}
}
//------------------------------------------------------------------------------------------------------------
FText UGB_AI_EQS::GetDescriptionTitle() const
{
	return FText::FromString(TEXT("Score by Nutrition"));
}
//------------------------------------------------------------------------------------------------------------
FText UGB_AI_EQS::GetDescriptionDetails() const
{
	return FText::FromString(TEXT("Higher Nutrition = Better Score"));
}
//------------------------------------------------------------------------------------------------------------
