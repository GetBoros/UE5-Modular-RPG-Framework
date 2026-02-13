//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stat.h>
#include <UI/TLG_Widget_Stat_Tooltip.h>

#include <Components/Image.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Stat
void UTLG_Widget_Stat::NativeConstruct()
{
    Super::NativeConstruct();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat::NativePreConstruct()
{
    if (ensureMsgf(TLG_Widget_Stat_Tooltip_Class, TEXT("TLG_Widget_Stat_Tooltip_Class not setting up") ) != true)
        return;
    
    if (TLG_Widget_Stat_Tooltip == 0)
    {
        TLG_Widget_Stat_Tooltip = CreateWidget<UTLG_Widget_Stat_Tooltip>(GetOwningPlayer(), TLG_Widget_Stat_Tooltip_Class);

        TLG_Widget_Stat_Tooltip->Update_TB_Description(Text_Tooltip_Description);
    }

    SetToolTip(TLG_Widget_Stat_Tooltip);
    Update_Stat(0.0f);

    Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat::Update_Stat(const float value)
{
    if (Image_Icon != 0  && Icon_Texture != 0)
        Image_Icon->SetBrushFromTexture(Icon_Texture);

    TB_Description->SetText(FText::AsNumber(value) );
}
//------------------------------------------------------------------------------------------------------------
