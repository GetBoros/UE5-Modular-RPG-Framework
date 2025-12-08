//------------------------------------------------------------------------------------------------------------
#include <GBG_Food.h>
#include <GameplayTagContainer.h>
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
    const FGameplayTag NutritionTag = FGameplayTag::RequestGameplayTag(FName("Test.StateTree.Tag2"));

    if (data_tag == NutritionTag)
    {
        out_value = NutritionValue;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------------------
