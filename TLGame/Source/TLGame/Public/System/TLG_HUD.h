//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/HUD.h>

#include <Data/TLG_Types.h>

#include <TLG_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_HUD;
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
	void Update_Buttons_Navigation(const TArray<FTLG_Location_Exit> &tlg_location_exits);
	void Update_Buttons_Actions(const TArray<FTLG_Location_Action> &tlg_location_action);
	void Handle_Game_Over();
	void Hide_Game_Over();

private:
	UTLG_Widget_HUD *Get_TLG_Widget_HUD();

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> HUD_Widget_Class;
	UPROPERTY() TObjectPtr<UTLG_Widget_HUD> HUD_Widget;
};
//------------------------------------------------------------------------------------------------------------
