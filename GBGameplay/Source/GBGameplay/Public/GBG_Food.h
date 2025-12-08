//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Interfaces/GBC_AI_Queryable_Interface.h>
#include <GameFramework/Actor.h>
#include <GBG_Food.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Food : public AActor, public IGBC_AI_Queryable_Interface
{
	GENERATED_BODY()

public:
	AGBG_Food();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual bool Query_Float_Value_By_Tag_Implementation(FGameplayTag data_tag, float& out_value) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float NutritionValue = 10.0f;

};
//------------------------------------------------------------------------------------------------------------
