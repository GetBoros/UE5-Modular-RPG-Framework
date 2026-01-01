//------------------------------------------------------------------------------------------------------------
#include <GBUI_HUD.h>
#include <GBUI_User_Widget.h>

#include <Blueprint/UserWidget.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerState.h>
#include <AbilitySystemComponent.h>
#include <AbilitySystemInterface.h>
//------------------------------------------------------------------------------------------------------------




// AGBUI_HUD
void AGBUI_HUD::BeginPlay()
{// !!! TEMP Maybe make a lot of methods

    IAbilitySystemInterface *ability_system_interface;
    APawn *controlled_pawn;
    APlayerState *player_state;
    APlayerController *player_controller;
    UGBUI_Widget_Controller *widget_controller;
    UAbilitySystemComponent *ability_system_component;
    UGBUI_User_Widget *gbui_user_widget;

    Super::BeginPlay();
    
    ensureMsgf(HUD_Widget_Class, L"Don`t forget set");
    ensureMsgf(Controller_Widget_Class, L"Don`t forget set");
    ensureMsgf(Attribute_Info_Data, L"Don`t forget set");

    // 1.0. HUD Init
    if (HUD_Widget_Class == 0)
        return;

    HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), HUD_Widget_Class);
    if (HUD_Widget == 0)
        return;
    HUD_Widget->AddToViewport();  // Must be last

    // 1.1. Get Player State and controlled pawn from player controller
    player_controller = GetOwningPlayerController();
    if (player_controller == 0)
        return;
    player_state = player_controller->PlayerState;
    controlled_pawn = player_controller->GetPawn();

    // 2.0. Get ASC from controlled pawn useing interface
    ability_system_interface = Cast<IAbilitySystemInterface>(controlled_pawn);  // Try to find interface if implented
    if (ability_system_interface == 0)
        ability_system_interface = Cast<IAbilitySystemInterface>(player_state);
    if (ability_system_interface == 0)
        return;
    ability_system_component = ability_system_interface->GetAbilitySystemComponent();
    
    // 3.0. Get and cache Widget Controller
    widget_controller = Get_Widget_Controller(FController_Widget_Params(player_controller, player_state, ability_system_component, Attribute_Info_Data) );

    // 3.1. Set Widget Controller to our base User Widget
    gbui_user_widget = Cast<UGBUI_User_Widget>(HUD_Widget);
    if (gbui_user_widget == 0)
        return;  // If parent not UGBUI_User_Widget return
    gbui_user_widget->Set_Widget_Controller(widget_controller);  // Pass the controller to the widget

    // 3.2. Finally if all settings are good, make broadcast and update value in HUD_Widget
    widget_controller->Broadcast_Initial_Values();  
}
//------------------------------------------------------------------------------------------------------------
void AGBUI_HUD::Show_Menu_Main()
{

}
//------------------------------------------------------------------------------------------------------------
UGBUI_Widget_Controller *AGBUI_HUD::Get_Widget_Controller(const FController_Widget_Params &params)
{
    if (Controller_Widget != 0)
        return Controller_Widget;

    if (Controller_Widget_Class == 0)
        return 0;

    Controller_Widget = NewObject<UGBUI_Widget_Controller>(this, Controller_Widget_Class);
    Controller_Widget->Init(params);

    return Controller_Widget;
}
//------------------------------------------------------------------------------------------------------------
