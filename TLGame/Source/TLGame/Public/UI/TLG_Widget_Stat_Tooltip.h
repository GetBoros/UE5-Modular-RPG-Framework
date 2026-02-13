//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Stat_Tooltip.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Stat_Tooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();
	virtual void NativePreConstruct();

	void Update_TB_Description(const FText &description);

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<UTextBlock> TB_Description;
};
//------------------------------------------------------------------------------------------------------------
