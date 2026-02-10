//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Abilities/TLG_Attribute_Set.h>
#include <GameplayTagContainer.h>
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
        tlg_game_state->On_Updated_Time.AddDynamic(this, &ATLG_Player_State::Handle_Time_Advanced);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Handle_Attribute_Sanity(float value) const
{
    const float sanity_to_apply = value;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;
    const FGameplayTag &gameplay_tag_state_sanity = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Sanity;

    // 1.0. Init
    if (Gameplay_Effect_Sanity_Class == 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec= Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Sanity_Class, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;
    gameplay_effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(gameplay_tag_state_sanity, sanity_to_apply);

	// 2.1. Apply the effect to self
    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Gameplay_Effect(const float value, const FGameplayTag &gameplay_tag_action, TSubclassOf<UGameplayEffect> gameplay_effect_class)
{
    FGameplayEffectContextHandle effect_handle_context;
    FGameplayEffectSpecHandle effect_handle_spec;
    const FGameplayTag &gameplay_tag_action_system_sleep = FTLG_Data_Gameplay_Tags::Get().Action_System_Sleep;

    // 1.0. Initializations
    effect_handle_context = Ability_System_Component->MakeEffectContext();
    effect_handle_context.AddSourceObject(this);
    effect_handle_spec = Ability_System_Component->MakeOutgoingSpec(gameplay_effect_class, 1.0f, effect_handle_context);
    if (effect_handle_spec.IsValid() != true)
        return;

    Ability_System_Component->AddLooseGameplayTag(gameplay_tag_action);  // Add action tag
    if (Ability_System_Component->HasMatchingGameplayTag(gameplay_tag_action_system_sleep) == true)
        effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(FTLG_Data_Gameplay_Tags::Get().Action_System_Sleep, -value);
    else
        effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(gameplay_tag_action, value);

    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*effect_handle_spec.Data.Get() );
    Ability_System_Component->RemoveLooseGameplayTag(gameplay_tag_action);  // Remove action tag after apply
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *ATLG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Handle_Time_Advanced(int32 hours, int32 minutes, int32 minutes_delta)
{
    const float fatigue_to_apply = static_cast<float>(minutes_delta) * Fatigue_Accumulation_Rate;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;
    const FGameplayTag &gameplay_tag_state_fatiigue = FTLG_Data_Gameplay_Tags::Get().State_Fatigued;

    // 1.0. Init
    if (Gameplay_Effect_Fatigue_Class == 0 || minutes_delta <= 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec= Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Fatigue_Class, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;
	
    gameplay_effect_handle_spec.Data.Get()->SetSetByCallerMagnitude(gameplay_tag_state_fatiigue, fatigue_to_apply);  // Apply fatigue
    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );  // Apply the effect to self
}
//------------------------------------------------------------------------------------------------------------