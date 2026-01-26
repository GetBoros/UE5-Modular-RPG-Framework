//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/HUD.h>
#include <Data/TLG_Types.h>

#include <TLG_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_HUD;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();

    void Dialogue_Show_Node(const FDialogue_Node &node);
    void Dialogue_Hide() const;

	void Set_Portrait_Texture(UTexture2D *texture);

private:
	UTLG_Widget_HUD *Get_TLG_Widget_HUD();

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> HUD_Widget_Class;
	UPROPERTY() TObjectPtr<UTLG_Widget_HUD> HUD_Widget;
};
//------------------------------------------------------------------------------------------------------------
