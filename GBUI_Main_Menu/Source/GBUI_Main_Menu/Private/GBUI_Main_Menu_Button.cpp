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

	ensureMsgf(Button_MI_BG, TEXT("Work if has this") );
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

	Play_Animation(1.0f, Button_DMI_BG);
	SetFocus();
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeOnMouseLeave(const FPointerEvent &in_mouse_event)
{
	Super::NativeOnMouseLeave(in_mouse_event);

	if (IsFocusable() != true)
		Play_Animation(0.0f, Button_DMI_BG);
}
//------------------------------------------------------------------------------------------------------------
FReply UGBUI_Main_Menu_Button::NativeOnFocusReceived(const FGeometry &in_geometry, const FFocusEvent &in_focus_event)
{
	Play_Animation(1.0f, Button_DMI_BG);

	return Super::NativeOnFocusReceived(in_geometry, in_focus_event);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::NativeOnFocusLost(const FFocusEvent &in_focus_event)
{
	Super::NativeOnFocusLost(in_focus_event);

	Play_Animation(0.0f, Button_DMI_BG);
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
void UGBUI_Main_Menu_Button::Init_Widget(UTextBlock *text, UImage *image)
{
	Button_TB = text;
	Button_Image = image;
	Button_DMI_BG = UMaterialInstanceDynamic::Create(Button_MI_BG, this);

	Button_TB->SetText(Button_Text);
	Button_Image->SetBrushFromMaterial(Button_DMI_BG);
	Button_DMI_BG->SetScalarParameterValue(Material_Scalar_Param, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void UGBUI_Main_Menu_Button::Play_Animation(const float value, UMaterialInstanceDynamic *material_instance_dynamic) const
{
	material_instance_dynamic->SetScalarParameterValue(Material_Scalar_Param, value);
}
//------------------------------------------------------------------------------------------------------------
