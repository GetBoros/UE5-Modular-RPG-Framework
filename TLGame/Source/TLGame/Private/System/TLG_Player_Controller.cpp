//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <System/TLG_Game_State.h>

#include <Components/TLG_Component_Dialogue.h>
#include <Components/TLG_Component_Navigation.h>

#include <Data/TLG_Data_Location.h>

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

    if (ensureMsgf(TLG_Data_Location_Current, TEXT("Is Empty, init from Game Mode or else") ) != true)
        return;

    if (ensureMsgf(TLG_Game_State, TEXT("Something whent wrong") ) != true)
        return;

    TLG_Component_Dialogue->Init(TLG_HUD, TLG_Player_State);
    TLG_Component_Navigation->Init(TLG_HUD, TLG_Game_State);

    Location_Enter(TLG_Data_Location_Current);

    TLG_Component_Navigation->On_Location_Enter.RemoveAll(this);
    TLG_Component_Navigation->On_Location_Enter.AddUObject(this, &ATLG_Player_Controller::Temp);

    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent == 0)
        return;

    InputComponent->BindKey(EKeys::BackSpace, IE_Pressed, this, &ATLG_Player_Controller::On_Pressed_ESC);  // !!! TEMP Change on EKeys::Escape
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Location_Enter(UTLG_Data_Location *tlg_data_location)
{
    TLG_Component_Navigation->Location_Enter(tlg_data_location);

	TLG_Location_Enemies = tlg_data_location->TLG_Location_Enemies;

    // Spawn_Location_Enemies(tlg_data_location->TLG_Location_Enemies);
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


    case ETLG_Game_Flow_Option::Quit_Game:
        UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
        break;
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Temp()
{
    Spawn_Location_Enemies();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Set_TLG_Data_Location_Current(UTLG_Data_Location *tlg_data_location)
{
    TLG_Data_Location_Current = tlg_data_location;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Spawn_Location_Enemies()
{
    float enemy_encounter_chance, roll_random;
    AActor *spawned_actor;
    TSubclassOf<AActor> enemy_class;
    FGameplayTagQuery enemy_condition_spawn;

    if (TLG_Location_Enemies.IsEmpty() == true)
        return;

    for (FTLG_Location_Enemy &tlg_location_enemie : TLG_Location_Enemies)
    {
        enemy_encounter_chance = tlg_location_enemie.Encounter_Chance;
        enemy_condition_spawn = tlg_location_enemie.Spawn_Conditions_Tag_Query;  // !!! TEMP Not used
        enemy_class = tlg_location_enemie.Enemy_Class;
        roll_random = FMath::FRand();  // 2. Generate value from 0.0 to 1.0

        spawned_actor = GetWorld()->SpawnActor<AActor>(enemy_class, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, FActorSpawnParameters() );

        // !!! TEMP If many enemies can be probles...
        if (roll_random <= enemy_encounter_chance)  // Begin dialugue if rolled
            TLG_Component_Dialogue->Dialogue_Start(FName("Intro"), tlg_location_enemie.TLG_Data_Enemy);  // !!! TEMP
        else
			TLG_Component_Dialogue->Dialogue_End();
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::On_Pressed_ESC()
{
    TLG_Game_State->Game_Menu_Paused();
}
//------------------------------------------------------------------------------------------------------------
