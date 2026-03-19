//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameFramework/PlayerController.h"
#include "GBG_Player_Controller.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputMappingContext;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn *pawn);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputMappingContext *Default_Mapping_Context;
};
//------------------------------------------------------------------------------------------------------------
