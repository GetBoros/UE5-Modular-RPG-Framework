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
	virtual void On_Widget_Controller_Set_Implementation();

private:
	void Add_Menu_Pause_Buttons(UVerticalBox *vertical_box);  // !!! TEMP
	void Handle_Game_Over();
	void Handle_Menu_Paused();
	void Handle_Game_Demo_Completed();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Menu_Pause;
    UPROPERTY(meta = (BindWidget, MultiLine = true) ) TObjectPtr<UTextBlock> TB_Game_State;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Flow> TLG_Widget_Button_Flow_Class;

};
//------------------------------------------------------------------------------------------------------------
