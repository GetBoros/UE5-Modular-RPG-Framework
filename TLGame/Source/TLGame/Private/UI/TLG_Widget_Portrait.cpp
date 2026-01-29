//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Portrait.h>

#include <Components/Image.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Portrait
void UTLG_Widget_Portrait::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Portrait::Set_Image_Portrait_Texture(UTexture2D *texture)
{
	Image_Portrait->SetBrushFromTexture(texture);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Portrait::Set_Image_Portrait_Visibility(const bool is_visible)
{
	if (is_visible == true)
		Image_Portrait->SetVisibility(ESlateVisibility::Visible);
	else
		Image_Portrait->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
