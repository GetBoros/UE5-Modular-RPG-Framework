//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "NativeGameplayTags.h"
#include <Interfaces/GBC_AI_Queryable_Interface.h>
#include "GameplayTagAssetInterface.h"
#include <GameFramework/Actor.h>
#include <GBG_Food.generated.h>
//------------------------------------------------------------------------------------------------------------
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TEST)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TEST_COMMENT)
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Food : public AActor, public IGBC_AI_Queryable_Interface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AGBG_Food();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual bool Query_Float_Value_By_Tag_Implementation(FGameplayTag data_tag, float& out_value) const override;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float NutritionValue = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags") FGameplayTagContainer GameplayTags;
};
//------------------------------------------------------------------------------------------------------------
