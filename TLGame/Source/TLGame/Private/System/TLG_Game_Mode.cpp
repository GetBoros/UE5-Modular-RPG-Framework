//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Game_Mode.h>
#include <System/TLG_Player_Controller.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Game_Mode
void ATLG_Game_Mode::BeginPlay()
{
    ATLG_Player_Controller *tlg_player_controller;

    Super::BeginPlay();

    if (ensureMsgf(Player_Start_Location, TEXT("Is empty") ) != true)
        return;

    tlg_player_controller = Cast<ATLG_Player_Controller>(GetWorld()->GetFirstPlayerController() );
    if (tlg_player_controller != 0)
        tlg_player_controller->Set_TLG_Data_Location_Current(Player_Start_Location);

}
//------------------------------------------------------------------------------------------------------------
