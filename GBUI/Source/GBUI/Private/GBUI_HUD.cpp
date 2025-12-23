//------------------------------------------------------------------------------------------------------------
#include <GBUI_HUD.h>
#include <GBUI_User_Widget.h>

#include <GAS/GBG_Attribute_Set.h> 
#include <GBG_Player.h> 

#include <Blueprint/UserWidget.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerState.h>
#include <AbilitySystemComponent.h>
#include <AbilitySystemInterface.h>
//------------------------------------------------------------------------------------------------------------




// AGBUI_HUD
void AGBUI_HUD::BeginPlay()
{// !!! TEMP Maybe make a lot of methods

    IAbilitySystemInterface *as_interface;
    APawn *controlled_pawn;
    APlayerState *ps;
    APlayerController *pc;
    AGBG_Player *gb_player;
    UAttributeSet *as;
    UGBUI_Widget_Controller *widget_controller;
    UAbilitySystemComponent *asc;
    UGBUI_User_Widget *smart_widget;

    Super::BeginPlay();
    
    // 1.0. HUD Init
    if (HUD_Widget_Class == 0)
        return;

    HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), HUD_Widget_Class);
    if (HUD_Widget == 0)
        return;
    HUD_Widget->AddToViewport();  // Must be last

    // 1.1. Get Player State and controlled pawn from player controller
    pc = GetOwningPlayerController();
    if (pc == 0)
        return;
    ps = pc->PlayerState;
    controlled_pawn = pc->GetPawn();

    // 2.0. Get ASC from controlled pawn useing interface
    as_interface = Cast<IAbilitySystemInterface>(controlled_pawn);
    if (as_interface == 0)
        return;
    asc = as_interface->GetAbilitySystemComponent();
    
    // 2.1. Get Attribute set from our controlled pawn
    gb_player = Cast<AGBG_Player>(controlled_pawn);  // Попытка 2: Получить AttributeSet через каст к нашему классу
    if (gb_player == 0)
        return;
    as = gb_player->GetAttributeSet();
    
    // 3.0. Create Controlled Widget Init
    FController_Widget_Params params(pc, ps, asc, as);
    params.Attribute_Info_Asset = Attribute_Info_Data;
    widget_controller = Get_Controller_Widget(params);

    // 3.1. Cast our "dumb" widget to our "smart" base class
    smart_widget = Cast<UGBUI_User_Widget>(HUD_Widget);
    if (smart_widget == 0)
        return;
    smart_widget->Set_Widget_Controller(widget_controller);  // Pass the controller to the widget
    widget_controller->Broadcast_Initial_Values();  // Need to broad cast data if bind after broadcast
}
//------------------------------------------------------------------------------------------------------------
UGBUI_Widget_Controller *AGBUI_HUD::Get_Controller_Widget(const FController_Widget_Params &params)
{
    if (Controller_Widget != 0)
        return Controller_Widget;

    if (Controller_Widget_Class == 0)
        return 0;

    Controller_Widget = NewObject<UGBUI_Widget_Controller>(this, Controller_Widget_Class);

    Controller_Widget->Set_Widget_Controller_Params(params);
    Controller_Widget->Bind_Callbacks_To_Dependencies();

    return Controller_Widget;
}
//------------------------------------------------------------------------------------------------------------
