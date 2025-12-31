////------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GBUI_Main_Menu_Button.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Button_Pressed);
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick)) class UGBUI_Main_Menu_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeOnMouseEnter(const FGeometry &in_geometry, const FPointerEvent &in_mouse_event);
	virtual void NativeOnMouseLeave(const FPointerEvent &in_mouse_event);
	virtual FReply NativeOnFocusReceived(const FGeometry &in_geometry, const FFocusEvent &in_focus_event);
	virtual void NativeOnFocusLost(const FFocusEvent &in_focus_event);
	virtual FReply NativeOnMouseButtonDown(const FGeometry &in_geometry, const FPointerEvent &in_mouse_event);
	virtual FReply NativeOnKeyDown(const FGeometry &in_geometry, const FKeyEvent &in_key_event);

	void Set_Material_Scalar(const float scalar, UMaterialInstanceDynamic *material_instance_dynamic) const;

	UMaterialInstanceDynamic *Button_DMI = 0;

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOn_Button_Pressed On_Button_Pressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true") ) FText Button_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true") ) FName Button_MI_Scalar_Param = FName("Hovered");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true") ) UMaterialInterface *Button_Material_Instance = 0;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UImage *Button_Image = 0;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UTextBlock *Button_TB = 0;
};
//------------------------------------------------------------------------------------------------------------
