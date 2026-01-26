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
    ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") );
    ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") );
    ensureMsgf(Ability_System_Component, TEXT("Not Implemented interface") );
    ensureMsgf(Dialogue_Data_Table, TEXT("Skip Dialogue_Start or can be crit error") );
    ensureMsgf(Current_Enemy_Data, TEXT("Skip Dialogue_Start or can be crit error") );
    
    // 3.0. Settings
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly() );

    Dialogue_Start(FName("Intro") );

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
    portrait = Current_Enemy_Data->Get_Portrait_By_Tag(next_node->Tag_Portrait);
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
