//------------------------------------------------------------------------------------------------------------
#include <System/TLG_HUD.h>
#include <System/TLG_Player_State.h>

#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Menu_Pause.h>
#include <UI/TLG_Widget_Controller.h>

#include <Abilities/TLG_Attribute_Set.h>
#include <Data/TLG_Data_Location.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_HUD
void ATLG_HUD::BeginPlay()
{
    if (ensureMsgf(TLG_Widget_HUD_Class, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Menu_Pause_Class, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;
    if (ensureMsgf(TLG_Widget_Controller_Class, TEXT("Is empty") ) != true)
        return;

    Init_Widget_Controller();

	Get_TLG_Widget_HUD()->Set_Widget_Controller(TLG_Widget_Controller);  // !!! TEMP Need refactoring
    Get_TLG_Widget_HUD()->Handle_Widget_Controller();
    
    Get_TLG_Widget_Menu_Pause()->Set_Widget_Controller(TLG_Widget_Controller);
    Get_TLG_Widget_Menu_Pause()->Handle_Widget_Controller();

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
void ATLG_HUD::Menu_Pause_Show()
{
    if (Get_TLG_Widget_HUD()->IsVisible() == true)
    {
        Get_TLG_Widget_HUD()->SetVisibility(ESlateVisibility::Collapsed);
        Get_TLG_Widget_Menu_Pause()->Init(ESlateVisibility::Visible);
    }
    else
    {
        Get_TLG_Widget_HUD()->SetVisibility(ESlateVisibility::Visible);
        Get_TLG_Widget_Menu_Pause()->Init(ESlateVisibility::Collapsed);
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_HUD::Init_Widget_Controller()
{
    APlayerController *player_controller;
    ATLG_Player_State *tlg_player_state;
    UAbilitySystemComponent *ability_system_component;
    UTLG_Attribute_Set *tlg_attribute_set;
    FController_Widget_Params controller_widget_params;

	if (TLG_Widget_Controller != 0)  // If already initialized
        return;

	// 1.0. Initialize reguired references
    player_controller = GetOwningPlayerController();
    if (player_controller == 0)
        return;

    tlg_player_state = player_controller->GetPlayerState<ATLG_Player_State>();
    if (tlg_player_state == 0)
        return;

    ability_system_component = tlg_player_state->GetAbilitySystemComponent();
    tlg_attribute_set = tlg_player_state->Get_Attribute_Set();
    if (ability_system_component == 0 || tlg_attribute_set == 0)
        return;

    controller_widget_params.Player_Controller = player_controller;
    controller_widget_params.Player_State = tlg_player_state;
    controller_widget_params.Ability_System_Component = ability_system_component;
    controller_widget_params.Attribute_Set = tlg_attribute_set;
    controller_widget_params.Attribute_Info = GBC_Attribute_Info;
    controller_widget_params.Game_State_Base = GetWorld()->GetGameState();

    // 2.0. Create and initialize tlg widget controller
    TLG_Widget_Controller = NewObject<UTLG_Widget_Controller>(this, TLG_Widget_Controller_Class);
    TLG_Widget_Controller->Init(controller_widget_params);

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
