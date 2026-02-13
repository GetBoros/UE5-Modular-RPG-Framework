//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <System/TLG_Game_State.h>

#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Data/TLG_Data_Enemy.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
#include <Components/AudioComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_Controller
void ATLG_Player_Controller::BeginPlay()
{
    UTLG_Attribute_Set *tlg_uattribute_set;

    // 1.0. Init
    TLG_HUD = GetHUD<ATLG_HUD>();
    TLG_Game_State = GetWorld()->GetGameState<ATLG_Game_State>();
    TLG_Player_State = GetPlayerState<ATLG_Player_State>();

    // 1.1. Bind delegates on attribute Sanity if zero
    if (TLG_Player_State != 0)
    {
        tlg_uattribute_set = TLG_Player_State->Get_Attribute_Set();
        tlg_uattribute_set->On_Sanity_Zero.AddUObject(this, &ATLG_Player_Controller::Handle_Game_Over);
    }

    // 2.0. Check
    if (ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;

    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;

    if (ensureMsgf(Dialogue_Data_Table, TEXT("Skip Location_Enter or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Enemy_Current, TEXT("Skip Location_Enter or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Location_Start, TEXT("Skip Location_Enter or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Game_State, TEXT("Something whent wrong") ) != true)
        return;

	// 3.0. Create audio component for ambient music
    if (Audio_Component_Ambient == 0)
    {
        Audio_Component_Ambient = NewObject<UAudioComponent>(this);
        Audio_Component_Ambient->RegisterComponent();  // Important for work
    }

    // 4.0. Actions
    Location_Enter(TLG_Data_Location_Start);

    // 4.1. Set input mode
    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI() );

    // 5.0. Blueprint logic
    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Location_Enter(UTLG_Data_Location *tlg_data_location)
{
    float roll;
    float enemy_encounter_chance;
    int location_enter_time_cost;
    USoundBase *sound_base;
    UTexture2D *texture2d_background;

    TLG_Data_Location_Current = tlg_data_location;
    location_enter_time_cost = 5;  // !!! TEMP Need add to data location
    enemy_encounter_chance = tlg_data_location->Enemy_Encounter_Chance;
    texture2d_background = tlg_data_location->Texture2D_Background_Image;
    sound_base = tlg_data_location->SoundBase_Ambient;
    roll = FMath::FRand();  // 2. Generate value from 0.0 to 1.0

    // 1.0. Background
    if (texture2d_background != 0)  // Update Background if have in tlg_data_location
        TLG_HUD->Set_Image_Texture_Background(texture2d_background);

    // 2.0. Music
    if (sound_base != 0)  // Play music
        Play_Ambient_Sound(sound_base);

    // 3.0. Dialogue
    if (roll <= enemy_encounter_chance)  // Begin dialugue if rolled
        Dialogue_Start(FName("Intro") );
    else
        TLG_HUD->Dialogue_Hide();

    // 4.0. Buttons Location and Actions
    TLG_HUD->Update_Buttons_Navigation(tlg_data_location->TLG_Location_Exits);
    TLG_HUD->Update_Buttons_Actions(tlg_data_location->TLG_Location_Action);

    // 5.0. Spend time when move to location
    TLG_Game_State->Advance_Time(location_enter_time_cost);

}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Location_Action(const FTLG_Location_Action &tlg_location_action)
{
    TLG_Game_State->Advance_Time(tlg_location_action.Time_Cost_Minutes);  // Spend time for interact with room action
    TLG_Player_State->Apply_Multy_Dynamic_Change(tlg_location_action);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Request_Game_Over_Flow(const ETLG_Game_Flow_Option tlg_game_flow_option)
{
    const FName current_level = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld() ) );

    switch (tlg_game_flow_option)
    {
    case ETLG_Game_Flow_Option::Continue:
        TLG_HUD->Hide_Game_Over();
        break;

    case ETLG_Game_Flow_Option::Restart_Level:
        UGameplayStatics::OpenLevel(GetWorld(), current_level);
        break;

    case ETLG_Game_Flow_Option::Quit_Game:
        UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
        break;

    case ETLG_Game_Flow_Option::MainMenu:
        break;
    }
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
void ATLG_Player_Controller::Handle_Player_Decision(const FPlayer_Response &player_response)
{
	const float response_cost = player_response.Response_Cost;
    FGameplayTag gameplay_tag;

	switch (player_response.Category)  // Apply response cost
    {
    case EDialogue_Response_Category::Aggressive:
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Dominance;
        break;

    case EDialogue_Response_Category::Logical:
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Empathy;
        break;

    case EDialogue_Response_Category::Silent:
        break;

    case EDialogue_Response_Category::Submissive:
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Sanity;
        break;

    default:
        break;
    }

    TLG_Player_State->Apply_Dynamic_Change(response_cost, gameplay_tag);

    // 1.1. Show next dialugue if next row exists
    if (player_response.Row_ID_Next.IsNone() != true)
        Dialogue_Start(player_response.Row_ID_Next);
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start(const FName &row_id)
{
    static const FString context(TEXT("Dialogue Context") );

    if (const FDialogue_Node *dialogue_node_next = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, context, true) )  // Find node by row id
    {
        TLG_HUD->Dialogue_Node_Show(*dialogue_node_next);  // Send data to Dialogue UI

        if (UTexture2D *texture_portrait = TLG_Data_Enemy_Current->Get_Portrait_By_Tag(dialogue_node_next->Tag_Portrait) )  // Set enemy portrait if have  in data
            TLG_HUD->Set_Image_Texture_Portrait(texture_portrait);
    }
    else
    {
        Dialogue_End();
    }
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_End()
{
    TLG_HUD->Dialogue_Hide();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::On_Pressed_ESC()
{
    TLG_HUD->Menu_Pause_Show();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Handle_Game_Over()
{
    TLG_HUD->Handle_Game_Over();
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
