//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GenericTeamAgentInterface.h>
#include <GameFramework/Character.h>

#include <GB_AI_Character.generated.h>
//------------------------------------------------------------------------------------------------------------
class AGB_AI_Controller;
class UED_AI_Stat_Component;
class UED_AI_Character_Stats;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API AGB_AI_Character : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGB_AI_Character();

	virtual void BeginPlay();  // Actor
	virtual void Tick(float delta_time);
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason);

	virtual void PossessedBy(AController *controller);  // Character
	virtual void UnPossessed();

	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component);
	virtual void PostInitializeComponents();

	virtual FGenericTeamId GetGenericTeamId() const;  // IGenericTeamAgentInterface

	float Get_Hunger() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") AGB_AI_Controller *AI_Controller;

};
//------------------------------------------------------------------------------------------------------------
