//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Abilities/TLG_Attribute_Set.h>

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
    Super::BeginPlay();

    if (ATLG_Game_State *tlg_game_state = GetWorld()->GetGameState<ATLG_Game_State>() )
        tlg_game_state->On_Time_Updated.AddDynamic(this, &ATLG_Player_State::Handle_Time_Advanced);
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
void ATLG_Player_State::Handle_Time_Advanced(int32 hours, int32 minutes, int32 minutes_delta)
{
    /* 24h 0.069 (Ciborg) 16h 0.104 (Norm) 12h 0.138 (Weak) 08h 0.208 (Sick) */
    constexpr float fatigue_accumulation_rate = 0.105f;  // 0.1f 16h 960min 96 Fatigue || 0.2f 8h 480min 96 fatigue
    const float fatigue_to_apply = static_cast<float>(minutes_delta) * fatigue_accumulation_rate;
    const FGameplayTag &gameplay_tag_state_fatiigue = FTLG_Data_Gameplay_Tags::Get().State_Fatigued;
    const FGameplayTag &gameplay_tag_action_system_sleep = FTLG_Data_Gameplay_Tags::Get().Action_System_Sleep;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;

    if (Gameplay_Effect_Fatigue_Class == 0 || minutes_delta <= 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);

    gameplay_effect_handle_spec= Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Fatigue_Class, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;

    if (Ability_System_Component->HasMatchingGameplayTag(gameplay_tag_action_system_sleep) == true)
        gameplay_effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(gameplay_tag_state_fatiigue, -fatigue_to_apply);
    else
        gameplay_effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(gameplay_tag_state_fatiigue, fatigue_to_apply);

    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------