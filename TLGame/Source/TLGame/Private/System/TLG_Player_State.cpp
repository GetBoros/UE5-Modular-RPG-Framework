//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
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
void ATLG_Player_State::Handle_Time_Advanced(int32 hours, int32 minutess)
{
    FGameplayEffectContextHandle gameplay_effect_context_handle;
    FGameplayEffectSpecHandle gameplay_effect_spec_handle;

    if (Ability_System_Component == 0 || GE_Fatigue_Class == 0)
        return;

    gameplay_effect_context_handle = Ability_System_Component->MakeEffectContext();
    gameplay_effect_spec_handle = Ability_System_Component->MakeOutgoingSpec(GE_Fatigue_Class, 1.0f, gameplay_effect_context_handle);

    if (gameplay_effect_spec_handle.IsValid() != true)
        return;

    gameplay_effect_spec_handle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.TimeDelta"), (float)minutess);
    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_spec_handle.Data.Get() );
}
//------------------------------------------------------------------------------------------------------------