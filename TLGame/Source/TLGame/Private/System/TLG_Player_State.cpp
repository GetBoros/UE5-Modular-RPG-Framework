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
    if (ensureMsgf(Gameplay_Effect_Class_Attributes, TEXT("Need HUD implemented from ATLG_HUD") ) != true)
        return;

    Super::BeginPlay();
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
void ATLG_Player_State::Apply_Multy_Dynamic_Change(const FTLG_Location_Action &tlg_location_action)
{
    float magnitude = 0.0f;
    int32 time_cost_minutes = tlg_location_action.Time_Cost_Minutes;
    FGameplayTag gameplay_tag_action = tlg_location_action.Gameplay_Tag_Action;
    const TArray<FTLG_Magnitude_Tag_Pair> &tlg_magnitude_tag_pair_array = tlg_location_action.TLG_Magnitude_Tag_Pair_Array;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;

    if (Gameplay_Effect_Class_Attributes == 0)
        return;

    gameplay_effect_handle_context = Ability_System_Component->MakeEffectContext();
    gameplay_effect_handle_context.AddSourceObject(this);
    gameplay_effect_handle_spec = Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Class_Attributes, 1.0f, gameplay_effect_handle_context);
    if (gameplay_effect_handle_spec.IsValid() != true)
        return;

    if (tlg_magnitude_tag_pair_array.Num() > 0)
    {
        for (const FTLG_Magnitude_Tag_Pair &tlg_magnitude_tag_pair : tlg_magnitude_tag_pair_array)
        {
            if (tlg_magnitude_tag_pair.Gameplay_Tag.IsValid() == true)
                gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(tlg_magnitude_tag_pair.Gameplay_Tag, tlg_magnitude_tag_pair.Magnitude);
        }
    }
    else
        gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(gameplay_tag_action, magnitude);

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
