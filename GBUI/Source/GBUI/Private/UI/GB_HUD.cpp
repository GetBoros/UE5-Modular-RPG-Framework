//------------------------------------------------------------------------------------------------------------
#include "UI/GB_HUD.h"

#include "Blueprint/UserWidget.h"
//------------------------------------------------------------------------------------------------------------




// AGB_HUD
void AGB_HUD::BeginPlay()
{
    Super::BeginPlay();

    if (Player_HUD_Widget_Class == 0)
        return;

    Player_HUD_Widget = CreateWidget<UUserWidget>(GetWorld(), Player_HUD_Widget_Class);
    if (Player_HUD_Widget == 0)
        return;

    Player_HUD_Widget->AddToViewport();
}
//------------------------------------------------------------------------------------------------------------
