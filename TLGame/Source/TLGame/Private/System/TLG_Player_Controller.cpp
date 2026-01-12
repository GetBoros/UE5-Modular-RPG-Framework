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
    Super::BeginPlay();
    
    ensureMsgf(Dialogue_Data_Table, TEXT("Can be useful") );

    if (Dialogue_Data_Table != 0)
        Dialogue_Start_Row(FName("Intro") );


    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Process_Player_Decision(const FPlayer_Response &choice)
{
    ATLG_HUD *hud = Get_TLG_HUD();

    if (choice.Sanity_Cost > 0.0f)
        Apply_Response_Cost(choice.Sanity_Cost);

    if (choice.Apply_Tags.IsValid() )
        Apply_Response_Effects(choice.Apply_Tags);  // Apply tag (Effects)

    if (choice.Next_Row_ID.IsNone() )
    {
        if (Get_TLG_HUD() != 0)
            Get_TLG_HUD()->Dialogue_Hide();
    }
    else
        Dialogue_Start_Row(choice.Next_Row_ID);
    
    UE_LOG(LogTemp, Warning, TEXT("Player chose: %s"), *choice.Response_Text.ToString() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Apply_Response_Cost(float cost)
{
    ATLG_Player_State *player_state;
    UAbilitySystemComponent *ability_system_component;

    player_state = Get_TLG_Player_State();
    if (player_state == 0)
        return;

    ability_system_component = player_state->GetAbilitySystemComponent();
    if (ability_system_component == 0)
        return;

    ability_system_component->ApplyModToAttribute(player_state->Get_Attribute_Set()->GetSanityAttribute(), EGameplayModOp::Additive, -cost);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Apply_Response_Effects(const FGameplayTagContainer &tags)
{
    ATLG_Player_State *player_state;
    UAbilitySystemComponent *ability_system_component;

    player_state = Get_TLG_Player_State();
    if (player_state == 0)
        return;

    ability_system_component = player_state->GetAbilitySystemComponent();
    if (ability_system_component == 0)
        return;
    
    ability_system_component->AddLooseGameplayTags(tags);  // !!! TEMP Add tags to player, in future split logic and for enemies
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Go_To_Next_Node(FName row_id)
{
    if (Dialogue_Data_Table == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Dialogue Data Table is NULL!") );
        return;
    }

    const FDialogue_Node* next_node = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, TEXT("Dialogue Context") );
    
    if (next_node != 0)
        Dialogue_Start(*next_node);
    else
        UE_LOG(LogTemp, Error, TEXT("Dialogue Row not found: %s"), *row_id.ToString());
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start(const FDialogue_Node& node)
{
    ATLG_HUD *tlg_hud = Get_TLG_HUD();

    if (tlg_hud == 0)
        return;
 
    tlg_hud->Dialogue_Show_Node(node);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Dialogue_Start_Row(FName row_id)
{
    ATLG_HUD *hud;
    FDialogue_Node *row_data;

    if (Dialogue_Data_Table == 0)
        return;

    // Ищем строку в таблице ContextString нужен для логов ошибок, если строка не найдется
    static const FString context_string(TEXT("Dialogue Context") );
    row_data = Dialogue_Data_Table->FindRow<FDialogue_Node>(row_id, context_string, true);

    if (row_data != 0)
    {
        hud = Get_TLG_HUD();

        if (hud != 0)
            hud->Dialogue_Show_Node(*row_data);  // Разыменовываем указатель (*row_data), так как функция ждет ссылку
    }
    else
        UE_LOG(LogTemp, Error, TEXT("Dialogue Row NOT FOUND: %s"), *row_id.ToString() );
}
//------------------------------------------------------------------------------------------------------------
ATLG_HUD *ATLG_Player_Controller::Get_TLG_HUD() const
{
    return GetHUD<ATLG_HUD>();
}
//------------------------------------------------------------------------------------------------------------
ATLG_Player_State *ATLG_Player_Controller::Get_TLG_Player_State() const
{
    return GetPlayerState<ATLG_Player_State>();
}
//------------------------------------------------------------------------------------------------------------
