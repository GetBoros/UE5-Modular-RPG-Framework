//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Stat.generated.h>
//------------------------------------------------------------------------------------------------------------
class UImage;
class UTextBlock;
class UTLG_Widget_Stat_Tooltip;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Stat : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();
	virtual void NativePreConstruct();

	UFUNCTION(BlueprintCallable) void Update_Stat(const float value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTexture2D> Icon_Texture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", MultiLine = true) ) FText Text_Tooltip_Description;  // !!! TEMP Make multy line
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Stat_Tooltip> TLG_Widget_Stat_Tooltip_Class;

	UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Icon;
	UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Description;

	UPROPERTY() TObjectPtr<UTLG_Widget_Stat_Tooltip> TLG_Widget_Stat_Tooltip;

};
//------------------------------------------------------------------------------------------------------------
