//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_Controller.h>
#include <System/TLG_Player_State.h>
#include <UI/TLG_Dialogue_Widget.h>

#include <Abilities/TLG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_Controller
void ATLG_Player_Controller::BeginPlay()
{
    ensureMsgf(Dialogue_Widget_Class, TEXT("Init in BP") );
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly() );

    if (Dialogue_Widget_Class == 0)
        return;

    Dialogue_Widget = CreateWidget<UTLG_Dialogue_Widget>(this, Dialogue_Widget_Class);
    if (Dialogue_Widget == 0)
        return;

    Dialogue_Widget->AddToViewport();
    Dialogue_Widget->SetVisibility(ESlateVisibility::Hidden);

    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
ATLG_Player_State *ATLG_Player_Controller::Get_TLG_Player_State() const
{
    return GetPlayerState<ATLG_Player_State>();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_Controller::Process_Player_Decision(const FPlayer_Response &choice)
{
    if (choice.Sanity_Cost > 0.0f)
        Apply_Response_Cost(choice.Sanity_Cost);

    if (choice.Apply_Tags.IsValid())
        Apply_Response_Effects(choice.Apply_Tags);  // Apply tag (Effects)

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