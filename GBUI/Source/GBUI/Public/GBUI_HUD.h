//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <GameFramework/HUD.h>
#include <GBUI_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUI_Widget_Controller;
class UGBC_Attribute_Info;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_API AGBUI_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();
    
	void Show_Menu_Main();

	UFUNCTION(BlueprintCallable, Category = "GBUI") UGBUI_Widget_Controller *Get_Widget_Controller(const FController_Widget_Params &params);

    UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> HUD_Widget_Class;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UGBUI_Widget_Controller> Controller_Widget_Class;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UGBC_Attribute_Info> Attribute_Info_Data;

private:
    UPROPERTY() UUserWidget *HUD_Widget;
	UPROPERTY() UGBUI_Widget_Controller *Controller_Widget;
};
//------------------------------------------------------------------------------------------------------------
