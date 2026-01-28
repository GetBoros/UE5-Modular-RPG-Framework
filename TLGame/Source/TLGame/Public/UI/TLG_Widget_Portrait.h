//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Blueprint/UserWidget.h"

#include "TLG_Widget_Portrait.generated.h"
//------------------------------------------------------------------------------------------------------------
class UImage;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Portrait : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct();

	void Set_Image_Portrait_Texture(UTexture2D *texture);
	void Is_Image_Portrait_Visible(const bool is_visible);

	UPROPERTY(meta = (BindWidget) ) UImage *Image_Portrait;

private:

};
//------------------------------------------------------------------------------------------------------------
