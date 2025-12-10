//------------------------------------------------------------------------------------------------------------
#include <GBG_Item_Data.h>
#include <GBGameplay.h>
#include <GameplayTagContainer.h>
//------------------------------------------------------------------------------------------------------------
UE_DEFINE_GAMEPLAY_TAG(TAG_TEST, "Food.Apple");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_TEST_COMMENT, "Food.Carrot", "Hello world");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Event_Explode, "Food.Sugar");
//------------------------------------------------------------------------------------------------------------




// UGBG_Item_Data
UGBG_Item_Data::UGBG_Item_Data()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Item_Data::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Item_Data::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//------------------------------------------------------------------------------------------------------------
bool UGBG_Item_Data::Query_Float_Value_By_Tag_Implementation(FGameplayTag data_tag, float& out_value) const
{
    if (data_tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Food"))))
    {
        out_value = NutritionValue;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------------------
void UGBG_Item_Data::GetOwnedGameplayTags(FGameplayTagContainer& tag_container) const
{
    tag_container.AppendTags(GameplayTags);
}
//------------------------------------------------------------------------------------------------------------
