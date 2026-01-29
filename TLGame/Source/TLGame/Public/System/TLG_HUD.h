//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/HUD.h>

#include <Data/TLG_Types.h>

#include <TLG_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_HUD;
struct FTLG_Location_Exit;
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
	void Update_Navigation_Buttons(const TArray<FTLG_Location_Exit> &tlg_location_exits);

private:
	UTLG_Widget_HUD *Get_TLG_Widget_HUD();

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> HUD_Widget_Class;
	UPROPERTY() TObjectPtr<UTLG_Widget_HUD> HUD_Widget;
};
//------------------------------------------------------------------------------------------------------------
