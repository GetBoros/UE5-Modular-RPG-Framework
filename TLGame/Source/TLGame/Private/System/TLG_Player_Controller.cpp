//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <System/TLG_HUD.h>

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
    ensureMsgf(Dialogue_Data_Table, TEXT("Need Dialogue_Data_Table to be valid or change to get ") );
    
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
    // 1.0. Apply response if needed
    if (choice.Sanity_Cost > 0.0f)
        Apply_Response_Cost(choice.Sanity_Cost);

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

    if (const FDialogue_Node *next_node = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, context, true) )
        TLG_HUD->Dialogue_Show_Node(*next_node);
    else
        Dialogue_End();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_End()
{
    TLG_HUD->Dialogue_Hide();

    SetInputMode(FInputModeGameOnly() );
    bShowMouseCursor = false;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Apply_Response_Cost(float cost)
{
    Ability_System_Component->ApplyModToAttribute(TLG_Player_State->Get_Attribute_Set()->GetSanityAttribute(), EGameplayModOp::Additive, -cost);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Apply_Response_Effects(const FGameplayTagContainer &tags)
{
    Ability_System_Component->AddLooseGameplayTags(tags);  // !!! TEMP Add tags to player, in future split logic and for enemies
}
//------------------------------------------------------------------------------------------------------------
