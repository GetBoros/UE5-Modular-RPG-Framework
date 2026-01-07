//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GBUIC_Widget_Controller.h>
#include <GameFramework/HUD.h>

#include <GBUI_Main_Menu_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUIC_Widget_Controller;
class UGBC_Attribute_Info;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_MAIN_MENU_API AGBUI_Main_Menu_HUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();  // !!! TEMP Maybe make a lot of methods

    UFUNCTION(BlueprintCallable) UGBUIC_Widget_Controller *Get_Widget_Controller(const FController_Widget_Params &params);

    UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> HUD_Widget_Class;
    UPROPERTY(EditDefaultsOnly) TSubclassOf<UGBUIC_Widget_Controller> Controller_Widget_Class;
    UPROPERTY(EditDefaultsOnly) TObjectPtr<UGBC_Attribute_Info> Attribute_Info_Data;

private:
    void Init();
    
    void Get_HUD_Widget();

    UPROPERTY() UUserWidget *HUD_Widget;
    UPROPERTY() UGBUIC_Widget_Controller *Controller_Widget;

};
//------------------------------------------------------------------------------------------------------------
