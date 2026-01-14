//------------------------------------------------------------------------------------------------------------
#include <System/TLG_HUD.h>

#include <UI/TLG_Widget_HUD.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_HUD
void ATLG_HUD::BeginPlay()
{
    Get_TLG_Widget_HUD();
    
    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Show_Node(const FDialogue_Node &node)
{
    Get_TLG_Widget_HUD()->Dialogue_Show_Node(node);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Hide() const
{
    if (HUD_Widget == 0)
        return;

    HUD_Widget->Dialogue_Hide();
}
//------------------------------------------------------------------------------------------------------------
UTLG_Widget_HUD *ATLG_HUD::Get_TLG_Widget_HUD()
{
    if (HUD_Widget != 0)
        return HUD_Widget;

    if (HUD_Widget_Class == 0)
        return 0;

    HUD_Widget = CreateWidget<UTLG_Widget_HUD>(GetOwningPlayerController(), HUD_Widget_Class);
    if (HUD_Widget != 0)
        HUD_Widget->AddToViewport();

    return HUD_Widget;
}
//------------------------------------------------------------------------------------------------------------
