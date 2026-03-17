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
    virtual void BeginPlay();  // !!! TEMP Refactoring

    UFUNCTION(BlueprintCallable) UGBUIC_Widget_Controller *Get_Widget_Controller(const FController_Widget_Params &params);

private:
    void Init();
    
    void Add_HUD_Widget_To_View_Port();

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> HUD_Widget_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UGBUIC_Widget_Controller> GBUIC_Widget_Controller_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBC_Attribute_Info> Attribute_Info_Data;

    UPROPERTY() UUserWidget *HUD_Widget;
    UPROPERTY() UGBUIC_Widget_Controller *GBUIC_Widget_Controller;

};
//------------------------------------------------------------------------------------------------------------
