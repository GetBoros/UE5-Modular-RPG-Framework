//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <System/TLG_Player_State.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    Super::NativeConstruct();

    Init_GAS_Attributes();  // For single it`s oke here
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Init_GAS_Attributes()
{
    APlayerController *player_controller;
    ATLG_Player_State *player_state;

    if (Ability_System_Component != 0 && Attribute_Set != 0)
        return;

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    player_state = player_controller->GetPlayerState<ATLG_Player_State>();
    if (player_state == 0)
        return;

    Ability_System_Component = player_state->GetAbilitySystemComponent();
    Attribute_Set = player_state->Get_Attribute_Set();

    if (Ability_System_Component == 0 || Attribute_Set == 0)
        return;
    
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Sanity);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Dominance);

    // Call BP Events to first init
    On_Updated_Sanity(Attribute_Set->GetSanity(), Attribute_Set->GetSanity_Max() );
    On_Updated_Dominance(Attribute_Set->GetDominance() );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Changed_Sanity(const FOnAttributeChangeData &data)
{
    float sanity_curr = data.NewValue;
    float sanity_max = 100.0f;

    if (Attribute_Set != 0)
        sanity_max = Attribute_Set->GetSanity_Max();

    On_Updated_Sanity(sanity_curr, sanity_max);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Changed_Dominance(const FOnAttributeChangeData &data)
{
    On_Updated_Dominance(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------