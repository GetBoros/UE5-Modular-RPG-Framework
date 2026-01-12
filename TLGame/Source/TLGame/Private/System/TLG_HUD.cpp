//------------------------------------------------------------------------------------------------------------
#include <System/TLG_HUD.h>

#include <UI/TLG_Widget_HUD.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_HUD
void ATLG_HUD::BeginPlay()
{
	Super::BeginPlay();

    if (HUD_Widget_Class == 0)
        return;

    HUD_Widget = CreateWidget<UTLG_Widget_HUD>(GetOwningPlayerController(), HUD_Widget_Class);
    if (HUD_Widget == 0)
        return;

    HUD_Widget->AddToViewport();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Show_Node(const FDialogue_Node &node)
{
    if (HUD_Widget == 0)
        return;

    HUD_Widget->Dialogue_Show_Node(node);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Hide()
{
    if (HUD_Widget == 0)
        return;

    HUD_Widget->Dialogue_Hide();
}
//------------------------------------------------------------------------------------------------------------
UTLG_Widget_HUD *ATLG_HUD::Get_TLG_Widget_HUD() const
{
    return HUD_Widget;
}
//------------------------------------------------------------------------------------------------------------
