//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Data/TLG_Data_Location.h>
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
void ATLG_Player_State::Temp(const FTLG_Location_Action &tlg_location_action)
{
    float magnitude = 0.0f;
    int32 time_cost_minutes = tlg_location_action.Time_Cost_Minutes;
    FGameplayTag gameplay_tag_action = tlg_location_action.Gameplay_Tag_Action;
    const TArray<FTLG_Magnitude_Tag_Pair> &tlg_magnitude_tag_pair_array = tlg_location_action.TLG_Magnitude_Tag_Pair_Array;

    if (tlg_magnitude_tag_pair_array.Num() > 0)
        Apply_Multy_Dynamic_Change(tlg_magnitude_tag_pair_array);
    else
        Apply_Dynamic_Change(magnitude, gameplay_tag_action);

}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *ATLG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set;
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
void ATLG_Player_State::Apply_Multy_Dynamic_Change(const TArray<FTLG_Magnitude_Tag_Pair> &TLG_Magnitude_Tag_Pair_array)
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

    for (const FTLG_Magnitude_Tag_Pair &tlg_magnitude_tag_pair : TLG_Magnitude_Tag_Pair_array)
    {
        if (tlg_magnitude_tag_pair.Gameplay_Tag.IsValid() == true)
            gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(tlg_magnitude_tag_pair.Gameplay_Tag, tlg_magnitude_tag_pair.Magnitude);
    }

    Ability_System_Component->ApplyGameplayEffectSpecToSelf(*gameplay_effect_handle_spec.Data.Get() );

}
//------------------------------------------------------------------------------------------------------------
