//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <System/TLG_Game_State.h>

#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Data/TLG_Data_Enemy.h>
#include <Data/TLG_Data_Location.h>

#include <Components/AudioComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_Controller
void ATLG_Player_Controller::BeginPlay()
{
    // 1.0. Init
    TLG_HUD = GetHUD<ATLG_HUD>();
    TLG_Game_State = GetWorld()->GetGameState<ATLG_Game_State>();
    TLG_Player_State = GetPlayerState<ATLG_Player_State>();

    // 2.0. Check
    if (ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;

    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Enemy_Current, TEXT("Skip Location_Enter or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Location_Current, TEXT("Is Empty, init from Game Mode or else") ) != true)
        return;

    if (ensureMsgf(TLG_Game_State, TEXT("Something whent wrong") ) != true)
        return;

	// 3.0. Create audio component for ambient music
    if (Audio_Component_Ambient == 0)
    {
        Audio_Component_Ambient = NewObject<UAudioComponent>(this);
        Audio_Component_Ambient->RegisterComponent();  // Important for work
    }

    // 4.0.
    Location_Enter(TLG_Data_Location_Current);

    // 4.1. Set input mode
    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI() );

    // 5.0
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
    int location_enter_time_cost;
    USoundBase *sound_base;
    UTexture2D *texture2d_background;

    TLG_Data_Location_Current = tlg_data_location;
    location_enter_time_cost = 5;  // !!! TEMP Need add to data location
    texture2d_background = tlg_data_location->Texture2D_Background_Image;
    sound_base = tlg_data_location->SoundBase_Ambient;

    // 1.0. Background
    if (texture2d_background != 0)  // Update Background if have in tlg_data_location
        TLG_HUD->Set_Image_Texture_Background(texture2d_background);

    // 2.0. Music
    if (sound_base != 0)  // Play music
        Play_Ambient_Sound(sound_base);

    // 3.0. Dialogue
    Spawn_Location_Enemies(tlg_data_location->TLG_Location_Enemies);

    // 4.0. Buttons Location and Actions
    TLG_HUD->Set_Location_Buttons(tlg_data_location->TLG_Location_Exits, tlg_data_location->TLG_Location_Actions);

    // 5.0. Spend time when move to location
    TLG_Game_State->Advance_Time(location_enter_time_cost);
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
void ATLG_Player_Controller::Handle_Player_Decision(const FPlayer_Response &player_response)
{
    TLG_Player_State->Apply_Multy_Dynamic_Change(player_response.Set_By_Caller_Magnitude);

    // 1.1. Show next dialugue if next row exists
    if (player_response.Row_ID_Next.IsNone() != true)
        Dialogue_Start(player_response.Row_ID_Next);
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Set_TLG_Data_Location_Current(UTLG_Data_Location *tlg_data_location)
{
    TLG_Data_Location_Current = tlg_data_location;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Set_Dialogue_Current(UDataTable *data_table)
{
    DT_Dialogue_Current = data_table;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Spawn_Location_Enemies(TArray<FTLG_Location_Enemy> tlg_location_enemies)
{
    float enemy_encounter_chance, roll_random;
    AActor *spawned_actor;
    TSubclassOf<AActor> enemy_class;
    FGameplayTagQuery enemy_condition_spawn;

    if (tlg_location_enemies.IsEmpty() == true)
        return;

    for (FTLG_Location_Enemy &tlg_location_enemie : tlg_location_enemies)
    {
        TLG_Data_Enemy_Current = tlg_location_enemie.TLG_Data_Enemy;
        enemy_encounter_chance = tlg_location_enemie.Encounter_Chance;
        enemy_condition_spawn = tlg_location_enemie.Spawn_Conditions_Tag_Query;  // !!! TEMP Not used
        enemy_class = tlg_location_enemie.Enemy_Class;
        roll_random = FMath::FRand();  // 2. Generate value from 0.0 to 1.0

        spawned_actor = GetWorld()->SpawnActor<AActor>(enemy_class, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, FActorSpawnParameters() );

        // !!! TEMP If many enemies can be probles...
        if (roll_random <= enemy_encounter_chance)  // Begin dialugue if rolled
            Dialogue_Start(FName("Intro") );  // !!! TEMP
        else
            TLG_HUD->Dialogue_Hide();
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start(const FName &row_id)
{
    static const FString context(TEXT("Dialogue Context") );

    if (DT_Dialogue_Current != 0)
    {
        if (FDialogue_Node *dialogue_node_next = DT_Dialogue_Current->FindRow<FDialogue_Node>(row_id, context, true) )  // Find node by row id
        {
            if (UTexture2D *texture_portrait_for_mood = TLG_Data_Enemy_Current->Get_Portrait_For_Mood(dialogue_node_next->Tag_Portrait) )
                TLG_HUD->Set_Image_Texture_Portrait(texture_portrait_for_mood);
            TLG_HUD->Dialogue_Node_Show(*dialogue_node_next);  // Send data to Dialogue UI
        }
    }
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_End()
{
    TLG_HUD->Dialogue_Hide();
    On_Dialogue_Ended.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::On_Pressed_ESC()
{
    TLG_Game_State->Game_Menu_Paused();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Play_Ambient_Sound(USoundBase *sound_base_to_play)
{
    if (Audio_Component_Ambient->Sound == sound_base_to_play && Audio_Component_Ambient->IsPlaying() )  // if already play return
        return;

    Audio_Component_Ambient->Stop();
    Audio_Component_Ambient->SetSound(sound_base_to_play);
    Audio_Component_Ambient->Play();
}
//------------------------------------------------------------------------------------------------------------
