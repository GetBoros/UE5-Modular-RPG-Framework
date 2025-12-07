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
void AGB_AI_Actor::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Actor::GetOwnedGameplayTags(FGameplayTagContainer &tag_container) const
{
	tag_container.AppendTags(Food_Tags);
}
//------------------------------------------------------------------------------------------------------------

