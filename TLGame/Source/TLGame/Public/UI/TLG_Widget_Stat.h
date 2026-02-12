//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Stat.generated.h>
//------------------------------------------------------------------------------------------------------------
class UImage;
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Stat : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();
	virtual void NativePreConstruct();

	UFUNCTION(BlueprintCallable) void Update_Value(float new_value);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTexture2D> Icon_Texture;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> Tooltip_Class;

	UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Icon;
	UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Description;

	UPROPERTY() TObjectPtr<UUserWidget> Cached_Tooltip;

};
//------------------------------------------------------------------------------------------------------------
