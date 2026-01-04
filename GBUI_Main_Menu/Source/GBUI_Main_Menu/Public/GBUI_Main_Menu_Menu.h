//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <GBUI_Main_Menu_Menu.generated.h>
//------------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UGBUI_Main_Menu_Button;
class UGBUIC_Widget_Controller_Menu;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class GBUI_MAIN_MENU_API UGBUI_Main_Menu : public UGBUIC_User_Widget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();
    virtual void NativeConstruct();

    //UFUNCTION(BlueprintPure, Category = "GBUI | Widget") UGBUIC_Widget_Controller_Menu *Get_Menu_Controller();
    UFUNCTION(BlueprintCallable) void Init();
    UFUNCTION(BlueprintCallable) void Handle_Button_New_Game();

    // !!! TEMP Experimental
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UVerticalBox *VB_Button_Container;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UUserWidget *Button_New_Game;

};
//------------------------------------------------------------------------------------------------------------
