//------------------------------------------------------------------------------------------------------------
#include <System/TLG_HUD.h>

#include <Data/TLG_Data_Location.h>
#include <UI/TLG_Widget_HUD.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_HUD
void ATLG_HUD::BeginPlay()
{
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
    HUD_Widget->Dialogue_Hide();
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
void ATLG_HUD::Update_Navigation_Buttons(const TArray<FTLG_Location_Exit> &tlg_location_exits)
{
    Get_TLG_Widget_HUD()->Update_Navigation_Buttons(tlg_location_exits);
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
