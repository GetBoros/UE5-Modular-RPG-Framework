//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/Actor.h>
#include <GBG_Food.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBG_Item_Data;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Food : public AActor
{
	GENERATED_BODY()

public:
	AGBG_Food();

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason);
	virtual void Tick(float delta_time);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UGBG_Item_Data *Item_Data_Component;
};
//------------------------------------------------------------------------------------------------------------
