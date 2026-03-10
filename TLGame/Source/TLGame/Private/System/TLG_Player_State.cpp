//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>

#include <Data/TLG_Types.h>
#include <Data/TLG_Data_Gameplay_Tags.h>

#include <Abilities/TLG_Attribute_Set.h>

#include <Types/GBC_Attribute_Info.h>

#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_State
ATLG_Player_State::ATLG_Player_State()
{
    Attribute_Set = CreateDefaultSubobject<UTLG_Attribute_Set>(TEXT("Attribute_Set") );
    Ability_System_Component = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability_System_Component") );
    
    if (Ability_System_Component == 0)
        return;

    Ability_System_Component->SetIsReplicated(true);
    Ability_System_Component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::BeginPlay()
{
    if (ensureMsgf(Gameplay_Effect_Class_Attributes, TEXT("Is empty") ) != true)
        return;

    Super::BeginPlay();

    Get_Attribute_Set()->On_Sanity_Zero.AddUObject(this, &ATLG_Player_State::Handle_Sanity_Zero);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *ATLG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set;
}
//------------------------------------------------------------------------------------------------------------
FGameplayAttribute ATLG_Player_State::Get_Attribute_By_Tag(const FGameplayTag &gameplay_tag_attribute) const
{
    if (GBC_Attribute_Info == 0)
        return FGameplayAttribute();

    const FGBC_Attribute_Info_Item &gbc_attribute_info_item = GBC_Attribute_Info->Find_Attribute_Info_By_Tag(gameplay_tag_attribute, true);

    if (gbc_attribute_info_item.Attribute_To_Bind.IsValid() )
        return gbc_attribute_info_item.Attribute_To_Bind;

    return FGameplayAttribute();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Multy_Dynamic_Change(const TArray<FTLG_Set_By_Caller_Magnitude> &set_by_caller_magnitude)
{
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;
    const TArray<FTLG_Set_By_Caller_Magnitude> &tlg_set_by_caller_magnitude_array = set_by_caller_magnitude;

    if (Gameplay_Effect_Class_Attributes == 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec = Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Class_Attributes, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;

    if (tlg_set_by_caller_magnitude_array.Num() > 0)
    {
        for (const FTLG_Set_By_Caller_Magnitude &tlg_set_by_caller_magnitude : tlg_set_by_caller_magnitude_array)
        {
            if (tlg_set_by_caller_magnitude.Attribute_Tag.IsValid() == true)
                gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(tlg_set_by_caller_magnitude.Attribute_Tag, tlg_set_by_caller_magnitude.Attribute_Magnitude);
        }
    }
    else
        gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Sanity, 0.0f);  // !!! TEMP

    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Dynamic_Change(float magnitude, FGameplayTag gameplay_tag)
{
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;

    if (Gameplay_Effect_Class_Attributes == 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec = Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Class_Attributes, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;

    gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(gameplay_tag, magnitude);
    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Temp(const FGameplayTagContainer gameplay_tag_container)
{
    // Ability_System_Component->TryActivateAbilityByClass();
    Ability_System_Component->TryActivateAbilitiesByTag(gameplay_tag_container);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Handle_Sanity_Zero()
{
    if (ATLG_Game_State *tlg_game_state = GetWorld()->GetGameState<ATLG_Game_State>() )
        tlg_game_state->Game_Over();
}
//------------------------------------------------------------------------------------------------------------
