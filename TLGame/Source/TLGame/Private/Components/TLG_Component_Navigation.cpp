//------------------------------------------------------------------------------------------------------------
#include <Components/TLG_Component_Navigation.h>

#include <System/TLG_HUD.h>
#include <System/TLG_Game_State.h>

#include <Subsystems/TLG_Subsystem_Story.h>
#include <Data/TLG_Data_Location.h>

#include <Components/AudioComponent.h>
//------------------------------------------------------------------------------------------------------------





// UTLG_Component_Navigation
UTLG_Component_Navigation::UTLG_Component_Navigation()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::Init(ATLG_HUD *tlg_hud, ATLG_Game_State *tlg_game_state)
{
    TLG_HUD = tlg_hud;
    TLG_Game_State = tlg_game_state;

    // 3.0. Create audio component for ambient music
    if (Audio_Component_Ambient == 0)
    {
        Audio_Component_Ambient = NewObject<UAudioComponent>(this);
        Audio_Component_Ambient->RegisterComponent();  // Important for work
    }

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::Location_Enter()
{
    int location_enter_time_cost;
    USoundBase *sound_base;
    UTexture2D *texture2d_background;

    location_enter_time_cost = 5;  // !!! TEMP Need add to data location
    texture2d_background = TLG_Data_Location_Current->Texture2D_Background_Image;
    sound_base = TLG_Data_Location_Current->SoundBase_Ambient;

    // 1.0. Background
    if (texture2d_background != 0)  // Update Background if have in TLG_Data_Location_Current
        TLG_HUD->Set_Image_Texture_Background(texture2d_background);

    // 2.0. Music
    if (sound_base != 0)  // Play music
        Play_Ambient_Sound(sound_base);

    // 3.0. Buttons Location and Actions
    TLG_HUD->Set_Location_Buttons(TLG_Data_Location_Current->TLG_Location_Exits, TLG_Data_Location_Current->TLG_Location_Actions);

    // 4.0. Change game time
    TLG_Game_State->Advance_Time(location_enter_time_cost);

    // 5.0. Delegate
    On_Location_Enter.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::Set_Location_Current(UTLG_Data_Location *tlg_data_location)
{
	TLG_Data_Location_Current = tlg_data_location;
}
//------------------------------------------------------------------------------------------------------------
UTLG_Data_Location *UTLG_Component_Navigation::Get_Location_Current()
{
    return TLG_Data_Location_Current;
}
//------------------------------------------------------------------------------------------------------------
UTLG_Data_Enemy *UTLG_Component_Navigation::Get_Location_Data_Enemy()
{
    float enemy_encounter_chance, roll_random;
    TArray<FTLG_Location_Enemy> &location_enemies = TLG_Data_Location_Current->TLG_Location_Enemies;

    for (FTLG_Location_Enemy &location_enemy: location_enemies)
    {
        enemy_encounter_chance = location_enemy.Encounter_Chance;
        roll_random = FMath::FRand();  // 2. Generate value from 0.0 to 1.0

        if (roll_random <= enemy_encounter_chance)  // Begin dialugue if rolled
        {
            Temp(location_enemy.Spawn_Conditions_Tag_Query, location_enemy.Enemy_Class);
            return location_enemy.TLG_Data_Enemy;
        }
    }

    return 0;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::Temp(const FGameplayTagQuery &spawn_conditions_tag_query, TSubclassOf<AActor> enemy_class)
{
    AActor *spawned_actor;
    UTLG_Subsystem_Story *subsystem_story;

    subsystem_story = GetWorld()->GetGameInstance()->GetSubsystem<UTLG_Subsystem_Story>();
    if (subsystem_story == 0)
        return;

    if (spawn_conditions_tag_query.Matches(subsystem_story->Get_Story_Flags()) != true)
        return;

    spawned_actor = GetWorld()->SpawnActor<AActor>(enemy_class, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, FActorSpawnParameters() );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Component_Navigation::Play_Ambient_Sound(USoundBase *sound_base_to_play)
{
    if (Audio_Component_Ambient->Sound == sound_base_to_play && Audio_Component_Ambient->IsPlaying() )  // if already play return
        return;

    Audio_Component_Ambient->Stop();
    Audio_Component_Ambient->SetSound(sound_base_to_play);
    Audio_Component_Ambient->Play();
}
//------------------------------------------------------------------------------------------------------------
