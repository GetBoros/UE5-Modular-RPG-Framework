//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayTagContainer.h>
#include <DetourCrowdAIController.h>

#include "GBAI_Controller.generated.h"
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_AI_Action_Requested_Delegate, const FGameplayTag &, requested_action_tag);
//------------------------------------------------------------------------------------------------------------
class UStateTreeAIComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API AGBAI_Controller : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
public:
	AGBAI_Controller();

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn *in_pawn);

	void Set_Patrol_Data(const float patrol_radius, const FVector patrol_center_location);
	
	UFUNCTION(BlueprintCallable, Category = "AI") void Handle_Game_Event(FGameplayTag event_tag, const UObject *payload);  // !!! TEMP EXAMPLE
	UFUNCTION(BlueprintCallable, Category = "AI") void Send_State_Tree_Event(const FGameplayTag gameplay_tag);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AI") FOn_AI_Action_Requested_Delegate On_AI_Action_Requested;

private:
	FDelegateHandle Handle_Listener_On_Is_Tag_Sugar;  // Handle ticket for unsub when needded
	void On_Is_Tag_Sugar(FGameplayTag tag, const UObject *payload);

	UFUNCTION(Category = "AI_Perception Event|Internal") void On_Target_Perception_Updated(AActor *actor, FAIStimulus stimulus);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) float Patrol_Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) FVector Patrol_Center_Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) AActor *Target_Actor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) UStateTreeAIComponent *AI_State_Tree;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) UAIPerceptionComponent *AI_Perception;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true") ) UAISenseConfig_Sight *AI_Sense_Config_Sight;

};
//------------------------------------------------------------------------------------------------------------
