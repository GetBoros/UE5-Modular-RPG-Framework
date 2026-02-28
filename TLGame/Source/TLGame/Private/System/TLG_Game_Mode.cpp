//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Game_Mode.h>

#include <Components/TLG_Component_Navigation.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Game_Mode
void ATLG_Game_Mode::BeginPlay()
{
    UTLG_Component_Navigation *tlg_component_navigation;
    Super::BeginPlay();

    if (ensureMsgf(Player_Start_Location, TEXT("Is empty") ) != true)
        return;

    tlg_component_navigation = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UTLG_Component_Navigation>();
    tlg_component_navigation->Set_Location_Current(Player_Start_Location);
}
//------------------------------------------------------------------------------------------------------------
