//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>
#include <GBUIC_User_Widget.h>

#include <TLG_Widget_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Stats_Bar;
class UTLG_Widget_Button;
class UTLG_Widget_Dialogue;
class UTLG_Widget_Portrait;
class UTLG_Widget_Button_Action;
class UTLG_Widget_Button_Navigation;
class UVerticalBox;
class UImage;
struct FTLG_Location_Exit;
struct FTLG_Location_Action;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_HUD : public UGBUIC_User_Widget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();
    virtual void On_Widget_Controller_Set_Implementation();

    void Dialogue_Node_Show(const FDialogue_Node &node_data);
    void Dialogue_Hide() const;

    void Set_Image_Texture_Background(UTexture2D *image_background_texture);
    void Set_Image_Texture_Portrait(UTexture2D *image_portrait_texture);
	void Update_Buttons_Navigation(const TArray<FTLG_Location_Exit> &tlg_location_exits);
	void Update_Buttons_Actions(const TArray<FTLG_Location_Action> &tlg_location_action);

private:
    void On_Game_Over();
    void On_Game_Resumed();
    void On_Game_Menu_Paused();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Background;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Navigation;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Actions;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Game_Over;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Dialogue> TLG_Widget_Dialogue;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Portrait> TLG_Widget_Portrait_Hero;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Portrait> TLG_Widget_Portrait_Enemy;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stats_Bar> TLG_Widget_Stats_Bar;

    UPROPERTY() TArray<TObjectPtr<UTLG_Widget_Button_Action> > TLG_Widget_Button_Action_Array;
    UPROPERTY() TArray<TObjectPtr<UTLG_Widget_Button_Navigation> > TLG_Widget_Button_Navigation_Array;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button> TLG_Widget_Button_Action_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button> TLG_Widget_Button_Navigation_Class;

};
//------------------------------------------------------------------------------------------------------------
