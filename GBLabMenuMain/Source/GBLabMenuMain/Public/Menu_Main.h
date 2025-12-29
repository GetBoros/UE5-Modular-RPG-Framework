//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GBLabMenuMain.h"
//------------------------------------------------------------------------------------------------------------
#include "Menu_Main.generated.h"
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Button_Pressed);
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UGBLab_Menu_Main_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();

	const FName Material_Scalar_Param = "Hovered";

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOn_Button_Pressed On_Button_Pressed;

	UFUNCTION(BlueprintCallable) void Init_Widget(UTextBlock *text, UImage *image);
	UFUNCTION(BlueprintCallable) void Play_Animation(const float value, UMaterialInstanceDynamic *material_instance_dynamic);

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UImage *Button_Image = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UTextBlock *Button_TB = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", ToolTip = "temp") ) FText Button_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", ToolTip = "temp") ) UMaterialInterface *Button_MI_BG= 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterialInstanceDynamic *Button_DMI_BG= 0;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class GBLABMENUMAIN_API UGBLab_Menu_Main: public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct();

};
//------------------------------------------------------------------------------------------------------------
