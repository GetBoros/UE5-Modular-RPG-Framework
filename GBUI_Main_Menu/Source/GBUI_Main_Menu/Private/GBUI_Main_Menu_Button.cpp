//------------------------------------------------------------------------------------------------------------
#include <GBUI_Main_Menu_Button.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu_Button 
void UGBUI_Main_Menu_Button::NativePreConstruct()
{
	Super::NativePreConstruct();

	ensureMsgf(Button_Material_Instance, TEXT("Need Material Instance with parameter Hovered") );
	if (Button_Material_Instance == 0)
		return;

	Button_DMI = UMaterialInstanceDynamic::Create(Button_Material_Instance, this);

	Button_TB->SetText(Button_Text);
	Button_Image->SetBrushFromMaterial(Button_DMI);
	Button_DMI->SetScalarParameterValue(Button_MI_Scalar_Param, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeConstruct()
{
	Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeOnMouseEnter(const FGeometry &in_geometry, const FPointerEvent &in_mouse_event)
{
	Super::NativeOnMouseEnter(in_geometry, in_mouse_event);

	Set_Material_Scalar(1.0f, Button_DMI);
	SetFocus();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeOnMouseLeave(const FPointerEvent &in_mouse_event)
{
	Super::NativeOnMouseLeave(in_mouse_event);

	if (IsFocusable() != true)
		Set_Material_Scalar(0.0f, Button_DMI);
}
//------------------------------------------------------------------------------------------------------------
FReply UGBUI_Main_Menu_Button::NativeOnFocusReceived(const FGeometry &in_geometry, const FFocusEvent &in_focus_event)
{
	Set_Material_Scalar(1.0f, Button_DMI);

	return Super::NativeOnFocusReceived(in_geometry, in_focus_event);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeOnFocusLost(const FFocusEvent &in_focus_event)
{
	Super::NativeOnFocusLost(in_focus_event);

	Set_Material_Scalar(0.0f, Button_DMI);
}
//------------------------------------------------------------------------------------------------------------
FReply UGBUI_Main_Menu_Button::NativeOnMouseButtonDown(const FGeometry &in_geometry, const FPointerEvent &in_mouse_event)
{
	On_Button_Pressed.Broadcast();

	return FReply::Handled();
}
//------------------------------------------------------------------------------------------------------------
FReply UGBUI_Main_Menu_Button::NativeOnKeyDown(const FGeometry &in_geometry, const FKeyEvent &in_key_event)
{
	if (in_key_event.GetKey() != EKeys::Enter)
		return FReply::Unhandled();

	On_Button_Pressed.Broadcast();

	return FReply::Handled();  // !!! TEMP Unhandled can be
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::Set_Material_Scalar(const float scalar, UMaterialInstanceDynamic *material_instance_dynamic) const
{
	material_instance_dynamic->SetScalarParameterValue(Button_MI_Scalar_Param, scalar);
}
//------------------------------------------------------------------------------------------------------------
