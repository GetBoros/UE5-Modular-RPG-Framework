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

    if (ASC != 0 && Attribute_Set != 0)
        return;

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    player_state = player_controller->GetPlayerState<ATLG_Player_State>();
    if (player_state == 0)
        return;

    ASC = player_state->GetAbilitySystemComponent();
    Attribute_Set = player_state->Get_Attribute_Set();

    if (ASC == 0 || Attribute_Set == 0)
        return;
    
    ASC->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Sanity_Changed);
    ASC->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Dominance_Changed);

    // Call BP Events to first init
    On_Sanity_Updated(Attribute_Set->GetSanity(), Attribute_Set->GetSanity_Max() );
    On_Dominance_Updated(Attribute_Set->GetDominance() );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Sanity_Changed(const FOnAttributeChangeData &data)
{
    float sanity_curr = data.NewValue;
    float sanity_max = 100.0f;

    if (Attribute_Set != 0)
        sanity_max = Attribute_Set->GetSanity_Max();

    On_Sanity_Updated(sanity_curr, sanity_max);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Dominance_Changed(const FOnAttributeChangeData &data)
{
    On_Dominance_Updated(data.NewValue);
}
//------------------------------------------------------------------------------------------------------------