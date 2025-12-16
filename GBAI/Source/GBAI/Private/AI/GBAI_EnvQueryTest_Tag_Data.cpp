//------------------------------------------------------------------------------------------------------------
#include <AI/GBAI_EnvQueryTest_Tag_Data.h>
#include <Interfaces/GBC_AI_Queryable_Interface.h>
#include <EnvironmentQuery/Items/EnvQueryItemType_Actor.h>
//------------------------------------------------------------------------------------------------------------




// UGBAI_EnvQueryTest_Tag_Data
UGBAI_EnvQueryTest_Tag_Data::UGBAI_EnvQueryTest_Tag_Data()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();

	TestPurpose = EEnvTestPurpose::Score;
}
//------------------------------------------------------------------------------------------------------------
void UGBAI_EnvQueryTest_Tag_Data::RunTest(FEnvQueryInstance &query_instance) const
{
    float queried_value;
    AActor *item_actor;
    UActorComponent *interface_comp;
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

        interface_comp = item_actor->FindComponentByInterface(UGBC_AI_Queryable_Interface::StaticClass() );
        if (interface_comp != 0 && IGBC_AI_Queryable_Interface::Execute_Query_Float_Value_By_Tag(interface_comp, Tag_Data_To_Query, queried_value) == true)
        {
            const float final_score = queried_value * multiplier_value;
            it.SetScore(TestPurpose, FilterType, final_score, FloatValueMin.GetValue(), FloatValueMax.GetValue() );
        }
        else
            it.ForceItemState(EEnvItemStatus::Failed);
    }
}
//------------------------------------------------------------------------------------------------------------
FText UGBAI_EnvQueryTest_Tag_Data::GetDescriptionTitle() const
{
    const FName tag_name_required = Tag_Required.IsValid() ? Tag_Required.GetTagName() : FName(TEXT("None") );
    const FName tag_name_data = Tag_Data_To_Query.IsValid() ? Tag_Data_To_Query.GetTagName() : FName(TEXT("None") );

    FString description = FString::Printf(TEXT("Required Tag: %s\nScores by Tag: %s"), *tag_name_required.ToString(), *tag_name_data.ToString() );

    return FText::FromString(description);
}
//------------------------------------------------------------------------------------------------------------
FText UGBAI_EnvQueryTest_Tag_Data::GetDescriptionDetails() const
{
	return FText::FromString(TEXT("Filter & Score by Tag Data") );
}
//------------------------------------------------------------------------------------------------------------
