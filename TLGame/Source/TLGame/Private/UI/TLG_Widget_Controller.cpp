//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Controller.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Types.h>

#include <Abilities/TLG_Attribute_Set.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Controller
void UTLG_Widget_Controller::Broadcast_Initial_Values()
{
    UTLG_Attribute_Set *tlg_attribute_set = Get_TLG_Attribute_Set();

    if (tlg_attribute_set == 0)
        return;

    Prev_Sanity = tlg_attribute_set->GetSanity();
    Prev_Empathy = tlg_attribute_set->GetEmpathy();
    Prev_Dominance = tlg_attribute_set->GetDominance();

    On_Changed_Sanity.Broadcast(Prev_Sanity, 0.0f);
    On_Changed_Empathy.Broadcast(Prev_Empathy, 0.0f);
    On_Changed_Dominance.Broadcast(Prev_Dominance, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Bind_Callbacks_To_Dependencies()
{
    ATLG_Game_State *tlg_game_state;
    UTLG_Attribute_Set *tlg_attribute_set;
    
	// 1.0. Bind Attribute Callbacks
    tlg_attribute_set = Get_TLG_Attribute_Set();
    if (Ability_System_Component == 0 || tlg_attribute_set == 0)
        return;

    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Sanity);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetEmpathyAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Empathy);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetFatigueAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Fatigue);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(tlg_attribute_set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Dominance);
    Ability_System_Component->RegisterGenericGameplayTagEvent().AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Gameplay_Tag);

    if (Attribute_Info != 0)
        FGBC_Attribute_Info_Item gbc_attribute_info_item_sanity = Attribute_Info->Find_Attribute_Info_By_Tag(FGameplayTag::RequestGameplayTag("Attribute.Player.Sanity") );

	// 1.1. Bind Game State Callbacks
    tlg_game_state = Cast<ATLG_Game_State>(Game_State_Base);
    if (tlg_game_state == 0)
        return;

    tlg_game_state->On_Updated_Time.AddDynamic(this, &UTLG_Widget_Controller::Handle_Changed_Time_Game);
    tlg_game_state->On_Updated_Day.AddDynamic(this, &UTLG_Widget_Controller::Handle_Changed_Day_Time);
	tlg_game_state->On_Game_Over.AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Game_Over);
	tlg_game_state->On_Game_Resumed.AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Game_Resumed);
	tlg_game_state->On_Game_Menu_Paused.AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Game_Menu_Paused);
	tlg_game_state->On_Game_Demo_Completed.AddUObject(this, &UTLG_Widget_Controller::Handle_Changed_Game_Demo_Completed);

    tlg_game_state->Broadcast_Game_Time_Current();
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
bool UTLG_Widget_Controller::Check_Action_Requirements(const TArray<FTLG_Action_Requirement> &tlg_action_requirement_array) const
{
    if (tlg_action_requirement_array.IsEmpty() )
        return true;  // if no requirements action possible

    for (const FTLG_Action_Requirement &tlg_action_requirement: tlg_action_requirement_array)
    {
        switch (tlg_action_requirement.Requirement_Type)
        {
        case ETLG_Requirement_Type::Attribute_Greater_Equal:
        {
            const float current_value = Ability_System_Component->GetNumericAttribute(tlg_action_requirement.Attribute);
            if (current_value < tlg_action_requirement.Value)
                return false;
            break;
        }


        case ETLG_Requirement_Type::Attribute_Less_Equal:
        {
            const float current_value = Ability_System_Component->GetNumericAttribute(tlg_action_requirement.Attribute);
            if (current_value > tlg_action_requirement.Value)
                return false;
            break;
        }


        case ETLG_Requirement_Type::Has_Gameplay_Tag:
        {
            if (!Ability_System_Component->HasMatchingGameplayTag(tlg_action_requirement.Attribute_Tag) )
                return false;
            break;
        }


        case ETLG_Requirement_Type::Missing_Gameplay_Tag:
        {
            if (Ability_System_Component->HasMatchingGameplayTag(tlg_action_requirement.Attribute_Tag) )
                return false;
            break;
        }


        }
    }

    return true;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Gameplay_Tag(const FGameplayTag gameplay_tag, int32 new_count)
{
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Sanity(const FOnAttributeChangeData &attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
	float delta = 0.0f;
    
    if (Prev_Sanity >= 0.0f)
        delta = current - Prev_Sanity;

    Prev_Sanity = current;

    On_Changed_Sanity.Broadcast(current, delta);
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Empathy(const FOnAttributeChangeData& attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
	float delta = 0.0f;
    
    if (Prev_Empathy >= 0.0f)
        delta = current - Prev_Empathy;

    Prev_Empathy = current;

    On_Changed_Empathy.Broadcast(current, delta);
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Fatigue(const FOnAttributeChangeData &attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
	float delta = 0.0f;
    
     if (Prev_Fatigued >= 0.0f)
         delta = current - Prev_Fatigued;

     Prev_Fatigued = current;

    On_Changed_Fatigued.Broadcast(current, delta);
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Dominance(const FOnAttributeChangeData &attribute_change_data)
{
    const float current = attribute_change_data.NewValue;
    float delta = 0.0f;

    if (Prev_Dominance >= 0.0f)
        delta = current - Prev_Dominance;

    Prev_Dominance = current;

    On_Changed_Dominance.Broadcast(current, delta);
    On_Player_Attribute_Changed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Game_Over()
{
    On_Game_Over.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Game_Resumed()
{
    On_Game_Resumed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Game_Menu_Paused()
{
    On_Game_Menu_Paused.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Game_Demo_Completed()
{
    On_Game_Demo_Completed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Time_Game(int32 hours, int32 minutes, int32 minutes_delta)
{
    On_Changed_Time_Game.Broadcast(hours, minutes);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Controller::Handle_Changed_Day_Time(int32 current_day)
{
    On_Changed_Day.Broadcast(current_day);
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *UTLG_Widget_Controller::Get_TLG_Attribute_Set() const
{
    return Cast<UTLG_Attribute_Set>(Attribute_Set);
}
//------------------------------------------------------------------------------------------------------------