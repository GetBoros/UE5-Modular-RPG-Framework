//------------------------------------------------------------------------------------------------------------
#include <GBUI.h>
#include <GBUI_HUD.h>

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
{
    IAbilitySystemInterface *as_interface;
    APawn *controlled_pawn;
    APlayerState *ps;
    APlayerController *pc;
    AGBG_Player *gb_player;
    UAttributeSet *as;
    UAbilitySystemComponent *asc;
    UGBUI_Widget_Controller *widget_controller;

    Super::BeginPlay();

    // 1.0. HUD Init
    if (HUD_Widget_Class == 0)
        return;

    HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), HUD_Widget_Class);
    if (HUD_Widget == 0)
        return;
    HUD_Widget->AddToViewport();

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
    widget_controller = Get_Controller_Widget(FController_Widget_Params(pc, ps, asc, as) );

    // 3. СВЯЗКА (View <-> Controller)
    // Пока мы просто создали контроллер. Виджет о нем еще не знает.
    // В следующем шаге мы научим Виджет принимать этот контроллер.
    // HUD_Widget->SetWidgetController(widget_controller); <--- ЭТО БУДЕТ ДАЛЬШЕ

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
