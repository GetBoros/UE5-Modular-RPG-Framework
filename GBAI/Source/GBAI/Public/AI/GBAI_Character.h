//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GenericTeamAgentInterface.h>
#include <GameFramework/Character.h>

#include <GBAI_Character.generated.h>
//------------------------------------------------------------------------------------------------------------
class AGBAI_Controller;
class UGBAI_Settings;
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType) class GBAI_API AGBAI_Character : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGBAI_Character();

	virtual void BeginPlay();  // Actor
	virtual void Tick(float delta_time);
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason);

	virtual void PossessedBy(AController *controller);  // Character
	virtual void UnPossessed();

	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component);
	virtual void PostInitializeComponents();

	virtual void PreInitializeComponents() override;


	virtual FGenericTeamId GetGenericTeamId() const;  // IGenericTeamAgentInterface

	float Get_Hunger() const;
	
	UFUNCTION() void Spawn_Loot(const FGameplayTag &requested_action_tag);

	const UGBAI_Settings* AI_Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") AGBAI_Controller *AI_Controller;
	UPROPERTY(EditAnywhere, Category = "Loot") TSoftClassPtr<AActor> Loot_Item_Class;

};
//------------------------------------------------------------------------------------------------------------
