//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Game_Mode.h>
#include <System/TLG_Player_Controller.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Game_Mode
void ATLG_Game_Mode::BeginPlay()
{
    Super::BeginPlay();

    ATLG_Player_Controller *tlg_player_controller = Cast<ATLG_Player_Controller>(GetWorld()->GetFirstPlayerController() );
    
    if (tlg_player_controller && Player_Start_Location)
        tlg_player_controller->Location_Enter(Player_Start_Location);
}
//------------------------------------------------------------------------------------------------------------
