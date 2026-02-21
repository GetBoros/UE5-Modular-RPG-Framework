//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Data_Location.h>
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
    Add_Gameplay_Tag_Story_Progresses(FTLG_Data_Gameplay_Tags::Get().Achievement_Tutorial_Intro);
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
bool ATLG_Player_State::Has_Gameplay_Tag_Story_Progresses(FGameplayTag new_tag)
{
    if (Gameplay_Tag_Story_Progresses.HasTag(new_tag) )
        return true;
    else
        return false;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Add_Gameplay_Tag_Story_Progresses(FGameplayTag new_tag)
{
    Gameplay_Tag_Story_Progresses.AddTag(new_tag);
}
//------------------------------------------------------------------------------------------------------------
bool ATLG_Player_State::Check_Requirement(const FTLG_Location_Action &tlg_location_action)
{
    float attribute_value = 0.0f;
    FGameplayAttribute gameplay_attribute;
    const TArray<FTLG_Requirement> &requirenments = tlg_location_action.TLG_Location_Action_Requirement;

	for (const FTLG_Requirement &requirenment : requirenments)  // for each requirement of the action
    {
		if (requirenment.Gameplay_Tag.IsValid() == true)  // if the requirement have a gameplay tag, check it
        {
            gameplay_attribute = Get_Attribute_By_Tag(requirenment.Gameplay_Tag);
            attribute_value = Ability_System_Component->GetNumericAttribute(gameplay_attribute);

			if (attribute_value >= requirenment.Value)  // if the attribute value is higher than the requirement value, return true, otherwise return false
            {
                if (requirenment.Is_Higher == true)
                    return true;  // if the requirement is higher, can apply the action
                else
					return false;  // if the requirement is not higher, can't apply the action
            }
            else
				return false;  // if the attribute value is lower than the requirement value can't apply the action
        }
    }

	return true;  // if don't have any requirement, return true
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Multy_Dynamic_Change(const FTLG_Location_Action &tlg_location_action)
{
    float magnitude = tlg_location_action.Attribute_Data_Magnitude;
    int32 time_cost_minutes = tlg_location_action.Time_Cost_Minutes;
    FGameplayTag gameplay_tag_attribute_data = tlg_location_action.Gameplay_Tag_Attribute_Data;
    FGameplayEffectContextHandle gameplay_effect_handle_context;
    FGameplayEffectSpecHandle gameplay_effect_handle_spec;
    const TArray<FTLG_Magnitude_Tag_Pair> &tlg_magnitude_tag_pair_array = tlg_location_action.TLG_Magnitude_Tag_Pair_Array;

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
        gameplay_effect_handle_spec.Data->SetSetByCallerMagnitude(gameplay_tag_attribute_data, magnitude);

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
void ATLG_Player_State::Handle_Sanity_Zero()
{
    if (ATLG_Game_State *tlg_game_state = GetWorld()->GetGameState<ATLG_Game_State>() )
        tlg_game_state->Game_Over();
}
//------------------------------------------------------------------------------------------------------------
