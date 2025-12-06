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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FGameplayTagContainer FoodTags;

};
//------------------------------------------------------------------------------------------------------------
