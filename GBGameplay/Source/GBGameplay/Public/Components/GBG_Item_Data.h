//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Interfaces/GBC_AI_Queryable_Interface.h>

#include <NativeGameplayTags.h>
#include <GameplayTagAssetInterface.h>
#include <Components/ActorComponent.h>

#include <GBG_Item_Data.generated.h>
//------------------------------------------------------------------------------------------------------------
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TEST)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TEST_COMMENT)
//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class GBGAMEPLAY_API UGBG_Item_Data : public UActorComponent, public IGBC_AI_Queryable_Interface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:	
	UGBG_Item_Data();

	virtual void BeginPlay();
	virtual void TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function);
	virtual void GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const;
	virtual bool Query_Float_Value_By_Tag_Implementation(const FGameplayTag &data_tag, float &out_value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float NutritionValue = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer GameplayTags;

};
//------------------------------------------------------------------------------------------------------------
