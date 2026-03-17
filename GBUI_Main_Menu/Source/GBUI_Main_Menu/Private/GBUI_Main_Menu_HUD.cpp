//------------------------------------------------------------------------------------------------------------
#include <GBUI_Main_Menu_HUD.h>
#include <GBUIC_User_Widget.h>

#include <Blueprint/UserWidget.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerState.h>
#include <AbilitySystemComponent.h>
#include <AbilitySystemInterface.h>
//------------------------------------------------------------------------------------------------------------




// AGBUI_Main_Menu_HUD
void AGBUI_Main_Menu_HUD::BeginPlay()
{
    Super::BeginPlay();
    
    if (ensureMsgf(HUD_Widget_Class, TEXT("Don`t forget set") ) == true)
    {
        HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), HUD_Widget_Class);

        HUD_Widget->AddToViewport();
    }

    return;  // !!! TEMP

    ensureMsgf(GBUIC_Widget_Controller_Class, TEXT("Don`t forget set") );
    ensureMsgf(Attribute_Info_Data, TEXT("Don`t forget set") );

    Init();
}
//------------------------------------------------------------------------------------------------------------
UGBUIC_Widget_Controller *AGBUI_Main_Menu_HUD::Get_Widget_Controller(const FController_Widget_Params &params)
{
    if (GBUIC_Widget_Controller != 0)
        return GBUIC_Widget_Controller;

    if (GBUIC_Widget_Controller_Class == 0)
        return 0;

    GBUIC_Widget_Controller = NewObject<UGBUIC_Widget_Controller>(this, GBUIC_Widget_Controller_Class);
    GBUIC_Widget_Controller->Init(params);

    return GBUIC_Widget_Controller;
}
//------------------------------------------------------------------------------------------------------------
void AGBUI_Main_Menu_HUD::Init()
{
    IAbilitySystemInterface *ability_system_interface;
    APawn *controlled_pawn;
    APlayerState *player_state;
    UGBUIC_User_Widget *gbui_user_widget;
    APlayerController *player_controller;
    UGBUIC_Widget_Controller *gbuic_widget_controller;
    UAbilitySystemComponent *ability_system_component;

    // 1.0. HUD Widget Create
    if (HUD_Widget_Class == 0)
        return;

    HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), HUD_Widget_Class);
    if (HUD_Widget == 0)
        return;

    // 1.1. Set Widget Controller to our base User Widget
    gbui_user_widget = Cast<UGBUIC_User_Widget>(HUD_Widget);
    if (gbui_user_widget == 0)
        return;  // If parent not UGBUIC_User_Widget return

    // 2.0. Get Player State and controlled pawn from player controller
    player_controller = GetOwningPlayerController();
    if (player_controller == 0)
        return;

    // 2.1. Get ASC from controlled pawn useing interface
    player_state = player_controller->PlayerState;
    controlled_pawn = player_controller->GetPawn();
    ability_system_interface = Cast<IAbilitySystemInterface>(controlled_pawn);  // Try to find interface if implemented
    if (ability_system_interface == 0)
        ability_system_interface = Cast<IAbilitySystemInterface>(player_state);
    if (ability_system_interface == 0)
        return;
    ability_system_component = ability_system_interface->GetAbilitySystemComponent();
    
    // 3.0. Get and cache Widget Controller
    gbuic_widget_controller = Get_Widget_Controller(FController_Widget_Params(player_controller, player_state, ability_system_component, 0, Attribute_Info_Data) );
    gbui_user_widget->Set_Widget_Controller(gbuic_widget_controller);  // Pass the controller to the widget
    gbuic_widget_controller->Broadcast_Initial_Values();  // 3.2. Finally if all settings are good, make broadcast and update value in HUD_Widget
}
//------------------------------------------------------------------------------------------------------------
