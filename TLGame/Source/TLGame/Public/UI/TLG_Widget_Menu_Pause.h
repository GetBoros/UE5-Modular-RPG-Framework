//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <TLG_Widget_Menu_Pause.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Button_Flow;
class UVerticalBox;
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Menu_Pause : public UGBUIC_User_Widget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

	void Init(const ESlateVisibility visibility);
	void Handle_Widget_Controller();

private:
	void Handle_Changed_Game_State();
	void Add_Menu_Pause_Buttons(UVerticalBox *vertical_box);

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Menu_Pause;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_Game_Over;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Flow> TLG_Widget_Button_Flow_Class;

};
//------------------------------------------------------------------------------------------------------------
