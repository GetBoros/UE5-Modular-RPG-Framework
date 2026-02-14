//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Menu_Pause.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Button_Flow;
class UVerticalBox;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Menu_Pause : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

	void Init();

private:
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Menu_Pause;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Flow> TLG_Widget_Button_Flow_Class;

};
//------------------------------------------------------------------------------------------------------------
