//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Text_Floating.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Text_Floating
void UTLG_Widget_Text_Floating::Setup_Visuals(const FText &text, const FLinearColor &color)
{
    TB_Floating->SetText(text);
    TB_Floating->SetColorAndOpacity(FSlateColor(color) );

    Play_Intro_Animation();
}
//------------------------------------------------------------------------------------------------------------
