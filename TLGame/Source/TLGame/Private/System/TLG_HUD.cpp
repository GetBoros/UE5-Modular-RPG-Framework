//------------------------------------------------------------------------------------------------------------
#include <System/TLG_HUD.h>
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Menu_Pause.h>
#include <Data/TLG_Data_Location.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_HUD
void ATLG_HUD::BeginPlay()
{
    if (ensureMsgf(TLG_Widget_HUD_Class, TEXT("Need HUD implemented from ATLG_HUD")) != true)
        return;

    if (ensureMsgf(TLG_Widget_Menu_Pause_Class, TEXT("Need Player State implemented from ATLG_Player_State")) != true)
        return;

    Get_TLG_Widget_HUD();
    
    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Node_Show(const FDialogue_Node &node)
{
    Get_TLG_Widget_HUD()->Dialogue_Node_Show(node);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Dialogue_Hide() const
{
    TLG_Widget_HUD->Dialogue_Hide();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Set_Image_Texture_Portrait(UTexture2D *texture)
{
    Get_TLG_Widget_HUD()->Set_Image_Texture_Portrait(texture);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Set_Image_Texture_Background(UTexture2D *texture2d)
{
    Get_TLG_Widget_HUD()->Set_Image_Texture_Background(texture2d);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Update_Buttons_Navigation(const TArray<FTLG_Location_Exit> &tlg_location_exits)
{
    Get_TLG_Widget_HUD()->Update_Buttons_Navigation(tlg_location_exits);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Update_Buttons_Actions(const TArray<FTLG_Location_Action> &tlg_location_action)
{
     Get_TLG_Widget_HUD()->Update_Buttons_Actions(tlg_location_action);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Menu_Pause_Show(const bool is_game_over)
{
    if (Get_TLG_Widget_HUD()->IsVisible() == true)
    {
        Get_TLG_Widget_HUD()->SetVisibility(ESlateVisibility::Collapsed);
        Get_TLG_Widget_Menu_Pause()->Init(ESlateVisibility::Visible, is_game_over);
    }
    else
    {
        Get_TLG_Widget_HUD()->SetVisibility(ESlateVisibility::Visible);
        Get_TLG_Widget_Menu_Pause()->Init(ESlateVisibility::Collapsed, is_game_over);
    }
}
//------------------------------------------------------------------------------------------------------------
UTLG_Widget_HUD *ATLG_HUD::Get_TLG_Widget_HUD()
{
    if (TLG_Widget_HUD != 0)
        return TLG_Widget_HUD;

    TLG_Widget_HUD = CreateWidget<UTLG_Widget_HUD>(GetOwningPlayerController(), TLG_Widget_HUD_Class);
    if (TLG_Widget_HUD != 0)
        TLG_Widget_HUD->AddToViewport();

    return TLG_Widget_HUD;
}
//------------------------------------------------------------------------------------------------------------
UTLG_Widget_Menu_Pause *ATLG_HUD::Get_TLG_Widget_Menu_Pause()
{
    if (TLG_Widget_Menu_Pause != 0)
        return TLG_Widget_Menu_Pause;

    TLG_Widget_Menu_Pause = CreateWidget<UTLG_Widget_Menu_Pause>(GetOwningPlayerController(), TLG_Widget_Menu_Pause_Class);
    if (TLG_Widget_Menu_Pause != 0)
        TLG_Widget_Menu_Pause->AddToViewport(-1);

    return TLG_Widget_Menu_Pause;
}
//------------------------------------------------------------------------------------------------------------
