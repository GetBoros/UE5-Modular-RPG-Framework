//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>
#include <Data/TLG_Enemy_Data.h>

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

    // 2.0. Check
    if (ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;

    if (ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") ) != true)
        return;

    if (ensureMsgf(Ability_System_Component, TEXT("Not Implemented interface") ) != true)
        return;

    if (ensureMsgf(Dialogue_Data_Table, TEXT("Skip Dialogue_Start or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Enemy_Data_Current, TEXT("Skip Dialogue_Start or can be crit error") ) != true)
        return;

    if (ensureMsgf(TLG_Data_Location_Start, TEXT("Skip Move_To_Location or can be crit error") ) != true)
        return;

    // 3.0. Settings
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly() );

    Move_To_Location(TLG_Data_Location_Start);
    //Dialogue_Start(FName("Intro") );

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
    UTexture2D *texture2d_background;
    
    TLG_Data_Location_Current = tlg_data_location;
    enemy_encounter_chance = tlg_data_location->Enemy_Encounter_Chance;
    texture2d_background = tlg_data_location->Texture2D_Background_Image;
    roll = FMath::FRand();  // 2. Generate value from 0.0 to 1.0

    if (texture2d_background != 0)  // Update Background if have in tlg_data_location
        TLG_HUD->Set_Image_Background_Texture(texture2d_background);

    if (roll <= enemy_encounter_chance)  // Begin dialugue if rolled
        Dialogue_Start(FName("Intro") );
    else
        TLG_HUD->Dialogue_Hide();

}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start(const FName &row_id)
{
    static const FString context(TEXT("Dialogue Context") );
    UTexture2D *portrait;
    FDialogue_Node *next_node;

	// 1.0. Find next dialogue node
	next_node = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, context, true);  // Find node by row id
    if (next_node == 0)
    {
        Dialogue_End();

        return;
    }

	TLG_HUD->Dialogue_Show_Node(*next_node);  // Send data to Dialogue UI

	// 2.0. Set enemy portrait if have  in data
    portrait = TLG_Enemy_Data_Current->Get_Portrait_By_Tag(next_node->Tag_Portrait);
    if (portrait == 0)
        return;

    TLG_HUD->Set_Portrait_Texture(portrait);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_End()
{
    TLG_HUD->Dialogue_Hide();

    SetInputMode(FInputModeGameOnly() );
    bShowMouseCursor = false;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Apply_Response_Effects(const FGameplayTagContainer &tags)
{
    Ability_System_Component->AddLooseGameplayTags(tags);  // !!! TEMP Add tags to player, in future split logic and for enemies
}
//------------------------------------------------------------------------------------------------------------
