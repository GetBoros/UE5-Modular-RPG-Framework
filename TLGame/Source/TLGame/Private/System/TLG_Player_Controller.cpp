//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <System/TLG_Game_State.h>

#include <Components/TLG_Component_Dialogue.h>
#include <Components/TLG_Component_Navigation.h>

#include <Internationalization/Internationalization.h>
#include <Internationalization/Culture.h>

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_Controller
ATLG_Player_Controller::ATLG_Player_Controller()
{
    TLG_Component_Dialogue = CreateDefaultSubobject<UTLG_Component_Dialogue>(TEXT("TLG_Component_Dialogue") );
    TLG_Component_Navigation = CreateDefaultSubobject<UTLG_Component_Navigation>(TEXT("TLG_Component_Navigation") );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::BeginPlay()
{
    // 1.0. Init
    TLG_HUD = GetHUD<ATLG_HUD>();
    TLG_Game_State = GetWorld()->GetGameState<ATLG_Game_State>();
    TLG_Player_State = GetPlayerState<ATLG_Player_State>();

    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI() );

    // 2.0. Check
    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;

    if (ensureMsgf(TLG_Game_State, TEXT("Something whent wrong") ) != true)
        return;

    TLG_Component_Dialogue->Init(TLG_HUD, TLG_Player_State);
    TLG_Component_Navigation->Init(TLG_HUD, TLG_Game_State);

    TLG_Component_Navigation->On_Location_Enter.RemoveAll(this);
    TLG_Component_Navigation->On_Location_Enter.AddUObject(this, &ATLG_Player_Controller::Handle_Location_Encounter);

    TLG_Component_Navigation->Location_Enter();

    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent == 0)
        return;

    InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &ATLG_Player_Controller::On_Pressed_ESC);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Location_Action(const FTLG_Location_Action &tlg_location_action)
{
    TLG_Player_State->Apply_Multy_Dynamic_Change(tlg_location_action.Set_By_Caller_Magnitude);
    TLG_Game_State->Advance_Time(tlg_location_action.Time_Cost_Minutes);  // Spend time for interact with room action
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Request_Menu_Main_Pause(const ETLG_Game_Flow_Option tlg_game_flow_option)
{
    const FName current_level = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld() ) );

    switch (tlg_game_flow_option)
    {
    case ETLG_Game_Flow_Option::Continue:
        TLG_Game_State->Game_Resume();
        break;


    case ETLG_Game_Flow_Option::Restart_Level:
        UGameplayStatics::OpenLevel(GetWorld(), current_level);
        break;


    case ETLG_Game_Flow_Option::Language_Change:
        if (FInternationalization::Get().GetCurrentCulture()->GetName().Contains(TEXT("ru") ) )
            FInternationalization::Get().SetCurrentCulture(TEXT("eng") );
        else
            FInternationalization::Get().SetCurrentCulture(TEXT("ru") );
        break;


    case ETLG_Game_Flow_Option::Quit_Game:
        UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
        break;
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Handle_Location_Encounter()
{
    UTLG_Data_Enemy *tlg_data_enemy = TLG_Component_Navigation->Get_Location_Data_Enemy();

    if (tlg_data_enemy != 0)
        TLG_Component_Dialogue->Dialogue_Start(FName("Intro"), tlg_data_enemy);
    else
        TLG_Component_Dialogue->Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::On_Pressed_ESC()
{
    TLG_Game_State->Game_Menu_Paused();
}
//------------------------------------------------------------------------------------------------------------
