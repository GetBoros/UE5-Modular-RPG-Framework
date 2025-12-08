//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
//#include <GameplayTagAssetInterface.h>
#include <GameFramework/Actor.h>
#include "GBG_Food.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Food : public AActor/*, public IGameplayTagAssetInterface*/
{
	GENERATED_BODY()

public:
	AGBG_Food();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	//virtual void GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float NutritionValue = 10.0f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FGameplayTagContainer Food_Tags;

};
//------------------------------------------------------------------------------------------------------------
