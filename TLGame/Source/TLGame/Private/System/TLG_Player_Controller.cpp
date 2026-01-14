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
    TLG_HUD = GetHUD<ATLG_HUD>();
    TLG_Player_State = GetPlayerState<ATLG_Player_State>();
    if (TLG_Player_State != 0)
        Ability_System_Component = TLG_Player_State->GetAbilitySystemComponent();

    ensureMsgf(TLG_HUD, TEXT("Need HUD implemented from ATLG_HUD") );
    ensureMsgf(TLG_Player_State, TEXT("Need Player State implemented from ATLG_Player_State") );
    ensureMsgf(Ability_System_Component, TEXT("Not Implemented interface") );
    ensureMsgf(Dialogue_Data_Table, TEXT("Can be useful") );
    
    if (Dialogue_Data_Table != 0)
        Dialogue_Start_Row(FName("Intro") );

    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly() );

    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Handle_Player_Decision(const FPlayer_Response &choice)
{
    if (choice.Sanity_Cost > 0.0f)
        Apply_Response_Cost(choice.Sanity_Cost);

    if (choice.Apply_Tags.IsValid() )
        Apply_Response_Effects(choice.Apply_Tags);  // Apply tag (Effects)

	if (choice.Next_Row_ID.IsNone() )  // If no next row, end dialogue
        TLG_HUD->Dialogue_Hide();
    else
        Dialogue_Start_Row(choice.Next_Row_ID);
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
void ATLG_Player_Controller::Go_To_Next_Node(FName row_id)
{
    const FDialogue_Node *next_node = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, TEXT("Dialogue Context") );
    
    if (next_node != 0)
        Dialogue_Start(*next_node);
    else
        UE_LOG(LogTemp, Error, TEXT("Dialogue Row not found: %s"), *row_id.ToString() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start(const FDialogue_Node& node)
{
    TLG_HUD->Dialogue_Show_Node(node);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start_Row(FName row_id)
{
    static const FString context_string(TEXT("Dialogue Context") );

    if (FDialogue_Node *row_data = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, context_string, true))
        TLG_HUD->Dialogue_Show_Node(*row_data);  // Why *? need &
    else
        UE_LOG(LogTemp, Error, TEXT("Dialogue Row NOT FOUND: %s"), *row_id.ToString() );  // !!! Or maybe call Dialogue_Show_Node with none node
}
//------------------------------------------------------------------------------------------------------------
