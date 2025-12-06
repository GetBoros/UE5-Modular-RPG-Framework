//------------------------------------------------------------------------------------------------------------
#include "AI/GB_AI_Actor.h"




// AGB_AI_Actor
AGB_AI_Actor::AGB_AI_Actor()
{
	PrimaryActorTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Actor::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Actor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(FoodTags);
}
//------------------------------------------------------------------------------------------------------------

