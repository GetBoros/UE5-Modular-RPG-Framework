//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "GB_AI_Actor.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API AGB_AI_Actor : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	AGB_AI_Actor();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float NutritionValue = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FGameplayTagContainer Food_Tags;

};
//------------------------------------------------------------------------------------------------------------
