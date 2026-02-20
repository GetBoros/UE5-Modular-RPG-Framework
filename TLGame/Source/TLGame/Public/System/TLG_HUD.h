//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/HUD.h>

#include <Data/TLG_Types.h>

#include <TLG_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBC_Attribute_Info;
class UTLG_Widget_HUD;
class UTLG_Widget_Menu_Pause;
class UTLG_Widget_Controller;
struct FTLG_Location_Exit;
struct FTLG_Location_Action;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();

    void Dialogue_Node_Show(const FDialogue_Node &node);
    void Dialogue_Hide() const;

	void Set_Image_Texture_Portrait(UTexture2D *texture);
	void Set_Image_Texture_Background(UTexture2D *texture2d);
	void Set_Location_Buttons(const TArray<FTLG_Location_Exit> &tlg_location_exits, const TArray<FTLG_Location_Action> &tlg_location_action);

private:
	void Init_Widget_Controller();
	UTLG_Widget_HUD *Get_TLG_Widget_HUD();
	UTLG_Widget_Menu_Pause *Get_TLG_Widget_Menu_Pause();

	void Update_Buttons_Navigation();
	void Update_Buttons_Actions();

	TArray<FTLG_Location_Exit> TLG_Location_Exit_Array;
	TArray<FTLG_Location_Action> TLG_Location_Action_Array;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_HUD> TLG_Widget_HUD_Class;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Menu_Pause> TLG_Widget_Menu_Pause_Class;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Controller> TLG_Widget_Controller_Class;

	UPROPERTY(Transient, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Widget_HUD> TLG_Widget_HUD;
	UPROPERTY(Transient, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Widget_Menu_Pause> TLG_Widget_Menu_Pause;
    UPROPERTY(Transient, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Widget_Controller> TLG_Widget_Controller;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBC_Attribute_Info> GBC_Attribute_Info;

};
//------------------------------------------------------------------------------------------------------------
