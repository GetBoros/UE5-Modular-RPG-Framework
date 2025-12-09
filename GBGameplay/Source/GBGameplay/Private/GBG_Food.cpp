//------------------------------------------------------------------------------------------------------------
#include <GBG_Food.h>
#include <GameplayTagContainer.h>
//------------------------------------------------------------------------------------------------------------
UE_DEFINE_GAMEPLAY_TAG(TAG_TEST, "Food.Apple");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_TEST_COMMENT, "Food.Carrot", "Hello world");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Event_Explode, "Food.Sugar");
//------------------------------------------------------------------------------------------------------------




// AGBG_Food
AGBG_Food::AGBG_Food()
{
	PrimaryActorTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
bool AGBG_Food::Query_Float_Value_By_Tag_Implementation(FGameplayTag data_tag, float& out_value) const
{
    //const FGameplayTag NutritionTag = FGameplayTag::RequestGameplayTag(FName("Test.StateTree.Tag2"));

    if (data_tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Food"))))
    {
        out_value = NutritionValue;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const
{
    tag_container.AppendTags(GameplayTags);
}
//------------------------------------------------------------------------------------------------------------
