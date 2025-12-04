//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "GB_AI_Controller.generated.h"
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_AI_Action_Event, const FGameplayTag &, event_tag);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API AGB_AI_Controller : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable, Category = "AI|State Tree") FOn_AI_Action_Event On_AI_Action_Event;
};
//------------------------------------------------------------------------------------------------------------
