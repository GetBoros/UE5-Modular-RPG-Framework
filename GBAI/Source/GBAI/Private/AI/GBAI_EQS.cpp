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
void UGBAI_EQS::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* QueryOwner = QueryInstance.Owner.Get();
    if (!QueryOwner)
        return;

    ScoreMultiplier.BindData(QueryOwner, QueryInstance.QueryID);
    const float MultiplierValue = ScoreMultiplier.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        if (!ItemActor)
        {
            It.ForceItemState(EEnvItemStatus::Failed);
            continue;
        }

        if (!ItemActor->Implements<UGBC_AI_Queryable_Interface>())
        {
            It.ForceItemState(EEnvItemStatus::Failed);
            continue;
        }

        // --- Happy Path: если все проверки пройдены, выполняем основную логику ---

        float QueriedValue = 0.0f;
        // Запрашиваем значение по тегу, который задан в редакторе
        if (IGBC_AI_Queryable_Interface::Execute_Query_Float_Value_By_Tag(ItemActor, DataToQueryTag, QueriedValue))
        {
            const float FinalScore = QueriedValue * MultiplierValue;
            // CHANGE: Используем встроенные в тест параметры для min/max
            It.SetScore(TestPurpose, FilterType, FinalScore, BoolValue.GetValue(), BoolValue.GetValue());
        }
        else
        {
            // Интерфейс есть, но на наш конкретный тег он ответить не смог
            It.ForceItemState(EEnvItemStatus::Failed);
        }
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
