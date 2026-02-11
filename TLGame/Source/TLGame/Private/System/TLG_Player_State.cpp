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

    // if (ATLG_Game_State *tlg_game_state = GetWorld()->GetGameState<ATLG_Game_State>() )
    //     tlg_game_state->On_Updated_Time.AddDynamic(this, &ATLG_Player_State::Handle_Time_Advanced);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Dynamic_Change(float value, FGameplayTag attribute_tag)
{
    float magnitude;
    FGameplayTag gameplay_tag;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;

    if (Gameplay_Effect_Class_Attributes == 0)
        return;

    gameplay_tag = attribute_tag;
    magnitude = value;
    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec = Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Class_Attributes, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;

    if (gameplay_tag.MatchesTag(FTLG_Data_Gameplay_Tags::Get().Action_System_Computer) )
    {
        magnitude = value * Fatigue_Accumulation_Rate;
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Fatigued;
    }
    else if (gameplay_tag.MatchesTag(FTLG_Data_Gameplay_Tags::Get().Action_System_Sleep) )
    {
        magnitude = -value;
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Fatigued;
    }

    gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(gameplay_tag, magnitude);
    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *ATLG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set;
}
//------------------------------------------------------------------------------------------------------------
