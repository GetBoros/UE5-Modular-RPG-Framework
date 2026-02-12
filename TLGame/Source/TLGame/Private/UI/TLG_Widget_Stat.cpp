//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stat.h>

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
    if (ensureMsgf(Tooltip_Class, TEXT("Floating Text Class not setting up")) != true)
        return;
    
    if (Cached_Tooltip == 0)
        Cached_Tooltip = CreateWidget<UUserWidget>(GetOwningPlayer(), Tooltip_Class);
    else
        SetToolTip(Cached_Tooltip);

    Update_Value(0.0f);

    Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat::Update_Value(float new_value)
{
    if (Image_Icon == 0  && Icon_Texture == 0)
        Image_Icon->SetBrushFromTexture(Icon_Texture);

    TB_Description->SetText(FText::AsNumber(new_value) );
}
//------------------------------------------------------------------------------------------------------------
