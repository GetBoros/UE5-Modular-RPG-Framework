//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stat.h>
#include <UI/TLG_Widget_Tooltip.h>

#include <Components/Image.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Stat
void UTLG_Widget_Stat::NativeConstruct()
{
    Super::NativeConstruct();

    if (TLG_Widget_Tooltip == 0)
    {
        TLG_Widget_Tooltip = CreateWidget<UTLG_Widget_Tooltip>(GetOwningPlayer(), TLG_Widget_Tooltip_Class);
        TLG_Widget_Tooltip->Update_TB_Description(Text_Tooltip_Description);
    }

    SetToolTip(TLG_Widget_Tooltip);

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (ensureMsgf(TLG_Widget_Tooltip_Class, TEXT("TLG_Widget_Tooltip_Class not setting up") ) != true)
        return;
    
    Update_Stat(0.0f);

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat::Update_Stat(const float value)
{
    if (Image_Icon != 0  && Icon_Texture != 0)
        Image_Icon->SetBrushFromTexture(Icon_Texture);

    TB_Description->SetText(FText::AsNumber(value) );
}
//------------------------------------------------------------------------------------------------------------
