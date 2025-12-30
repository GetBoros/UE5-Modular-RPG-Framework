//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <GBUI_Menu.generated.h>
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

	const FName Material_Scalar_Param = "Hovered";

	UFUNCTION(BlueprintCallable) void Update_Hover_State(bool b_is_hovered);
	UFUNCTION(BlueprintCallable) void Init_Widget(UTextBlock *text, UImage *image);
	UFUNCTION(BlueprintCallable) void Play_Animation(const float value, UMaterialInstanceDynamic *material_instance_dynamic);

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOn_Button_Pressed On_Button_Pressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UImage *Button_Image = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UTextBlock *Button_TB = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", ToolTip = "temp") ) FText Button_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", ToolTip = "temp") ) UMaterialInterface *Button_MI_BG = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterialInstanceDynamic *Button_DMI_BG = 0;
	UPROPERTY(EditAnywhere) TObjectPtr<UMaterialInterface> Hover_Material;

};
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick)) class GBUI_MAIN_MENU_API UGBUI_Main_Menu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();

};
//------------------------------------------------------------------------------------------------------------
