//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>
#include <NativeGameplayTags.h>

#include <GBUI_Main_Menu_Menu.generated.h>
//------------------------------------------------------------------------------------------------------------
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_MENU_NEW_GAME)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_MENU_LOAD)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_MENU_SETTINGS)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_MENU_EXIT)
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

private:
    void Init();

    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Button_New_Game();
    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Button_Load();
    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Button_Settings();
    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Button_Exit();

    UFUNCTION(BlueprintPure, meta = (AllowPrivateAccess = "true") ) UGBUIC_Widget_Controller_Menu *Get_Menu_Controller();
    
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true") ) UVerticalBox *VB_Button_Container;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true") ) UUserWidget *Button_New_Game;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true") ) UUserWidget *Button_Load;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true") ) UUserWidget *Button_Settings;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true") ) UUserWidget *Button_Exit;

};
//------------------------------------------------------------------------------------------------------------
