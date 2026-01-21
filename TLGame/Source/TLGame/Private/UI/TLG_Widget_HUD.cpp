//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Dialogue.h>
#include <System/TLG_Player_State.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
#include <Components/Image.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    Init();  // For single it`s oke here

    ensureMsgf(Attribute_Set, TEXT("Init_GAS_Attributes can`t get Attribute_Set") );
    ensureMsgf(Ability_System_Component, TEXT("Init_GAS_Attributes can`t get Ability_System_Component") );
 
    Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Init()
{
    APlayerController *player_controller;
    ATLG_Player_State *player_state;

	// 1.0. Get Player State and its Ability System Component + Attribute Set
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
    
	// 1.1. Bind delegates for attribute changes
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Sanity);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Dominance);

    // 2.0. Call BP Events to first init
    On_Updated_Sanity(Attribute_Set->GetSanity(), Attribute_Set->GetSanity_Max() );
    On_Updated_Dominance(Attribute_Set->GetDominance() );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Show_Node(const FDialogue_Node &node_data) const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Visible);
    TLG_Widget_Dialogue->Setup_Dialogue_Node(node_data);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Hide() const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Hidden);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Background_Texture(UTexture2D *image_background_texture) const
{
    Image_Background->SetBrushFromTexture(image_background_texture);
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