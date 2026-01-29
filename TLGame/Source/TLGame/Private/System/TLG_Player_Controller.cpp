//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <Data/TLG_Data_Enemy.h>

#include <Components/AudioComponent.h>

#include <Abilities/TLG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_Controller
void ATLG_Player_Controller::BeginPlay()
{
    // 1.0. Init
    TLG_HUD = GetHUD<ATLG_HUD>();
    TLG_Player_State = GetPlayerState<ATLG_Player_State>();
    if (TLG_Player_State != 0)
        Ability_System_Component = TLG_Player_State->GetAbilitySystemComponent();

    if (Audio_Component_Ambient == 0)
    {
        Audio_Component_Ambient = NewObject<UAudioComponent>(this);
        Audio_Component_Ambient->RegisterComponent();  // Important for work
    }

    // 2.0. Check
    if (ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;

    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;

    if (ensureMsgf(Ability_System_Component, TEXT("Not Implemented interface") ) != true)
        return;

    if (ensureMsgf(Dialogue_Data_Table, TEXT("Skip Dialogue_Start or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Enemy_Current, TEXT("Skip Dialogue_Start or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Location_Start, TEXT("Skip Move_To_Location or can be crit error") ) != true)
        return;

    // 3.0. Actions
    Move_To_Location(TLG_Data_Location_Start);

    // 4.0. Blueprint logic
    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Handle_Player_Decision(const FPlayer_Response &choice)
{
	const float response_cost = choice.Response_Cost;

	switch (choice.Category)  // Apply response cost
    {
    case EDialogue_Response_Category::Aggressive:
        Ability_System_Component->ApplyModToAttribute(TLG_Player_State->Get_Attribute_Set()->GetDominanceAttribute(), EGameplayModOp::Additive, response_cost);
        break;

    case EDialogue_Response_Category::Logical:
        Ability_System_Component->ApplyModToAttribute(TLG_Player_State->Get_Attribute_Set()->GetEmpathyAttribute(), EGameplayModOp::Additive, response_cost);

        break;

    case EDialogue_Response_Category::Silent:
        break;

    case EDialogue_Response_Category::Submissive:
        Ability_System_Component->ApplyModToAttribute(TLG_Player_State->Get_Attribute_Set()->GetSanityAttribute(), EGameplayModOp::Additive, response_cost);
        break;

    default:
        break;
    }

    if (choice.Tags_Apply.IsValid() )
        Apply_Response_Effects(choice.Tags_Apply);  // Apply tag (Effects)

    // 1.1. Show next dialugue if next row exists
    if (choice.Row_ID_Next.IsNone() != true)
        Dialogue_Start(choice.Row_ID_Next);
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Move_To_Location(UTLG_Data_Location *tlg_data_location)
{
    float roll;
    float enemy_encounter_chance;
    USoundBase *sound_base;
    UTexture2D *texture2d_background;
    
    TLG_Data_Location_Current = tlg_data_location;
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

    // 4.0. Buttons
    TLG_HUD->Update_Navigation_Buttons(tlg_data_location->TLG_Location_Exits);
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

        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly() );
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
void ATLG_Player_Controller::Apply_Response_Effects(const FGameplayTagContainer &tags)
{
    Ability_System_Component->AddLooseGameplayTags(tags);  // !!! TEMP Add tags to player, in future split logic and for enemies
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
