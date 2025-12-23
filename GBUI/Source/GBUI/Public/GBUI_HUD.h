//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <GameFramework/HUD.h>
#include <GBUI_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUI_Widget_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_API AGBUI_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();
    
	UFUNCTION(BlueprintCallable, Category = "GBUI") UGBUI_Widget_Controller *Get_Controller_Widget(const FController_Widget_Params &params);

    UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> HUD_Widget_Class;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UGBUI_Widget_Controller> Controller_Widget_Class;

private:
    UPROPERTY() UUserWidget *HUD_Widget;
	UPROPERTY() UGBUI_Widget_Controller *Controller_Widget;
};
//------------------------------------------------------------------------------------------------------------
