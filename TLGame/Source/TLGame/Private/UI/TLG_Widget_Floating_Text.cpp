//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Floating_Text.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_FloatingText
void UTLG_Widget_Floating_Text::Setup_Visuals(const FText &text, const FLinearColor &color)
{
    TB_Floating->SetText(text);
    TB_Floating->SetColorAndOpacity(FSlateColor(color) );

    Play_Intro_Animation();
}
//------------------------------------------------------------------------------------------------------------
