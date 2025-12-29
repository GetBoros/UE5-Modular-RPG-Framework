//------------------------------------------------------------------------------------------------------------
#include <GBUI_Menu.h>

#include <Materials/MaterialInstanceDynamic.h>

#include <Components/Image.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu_Button 
void UGBUI_Main_Menu_Button::NativePreConstruct()
{
	Super::NativePreConstruct();
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
void UGBUI_Main_Menu_Button::Play_Animation(const float value, UMaterialInstanceDynamic *material_instance_dynamic)
{
	material_instance_dynamic->SetScalarParameterValue(Material_Scalar_Param, value);
}
//------------------------------------------------------------------------------------------------------------




// UGBUI_Main_Menu
void UGBUI_Main_Menu::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
