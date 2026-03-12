//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_Widget_Controller.h>

#include <TLG_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOn_Player_Attribute_Changed);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Over);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Resumed);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Menu_Paused);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Demo_Completed);
DECLARE_MULTICAST_DELEGATE_OneParam(FOn_Day_Updated_Signature, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOn_Attribute_Changed_Signature, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOn_Time_Updated_Signature, int32, int32);
//------------------------------------------------------------------------------------------------------------
class UTLG_Attribute_Set;
struct FTLG_Action_Requirement;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Controller : public UGBUIC_Widget_Controller
{
    GENERATED_BODY()

public:
    virtual void Broadcast_Initial_Values();
    virtual void Bind_Callbacks_To_Dependencies();

    void Request_Ability_Activation(const FGameplayTag &gameplay_tag) const;
    bool Check_Action_Requirements(const TArray<FTLG_Action_Requirement> &tlg_action_requirement_array) const;

    FOn_Game_Over On_Game_Over;
    FOn_Game_Resumed On_Game_Resumed;
    FOn_Game_Menu_Paused On_Game_Menu_Paused;
    FOn_Game_Demo_Completed On_Game_Demo_Completed;
    FOn_Player_Attribute_Changed On_Player_Attribute_Changed;

    FOn_Attribute_Changed_Signature On_Changed_Sanity;
    FOn_Attribute_Changed_Signature On_Changed_Empathy;
    FOn_Attribute_Changed_Signature On_Changed_Fatigued;
    FOn_Attribute_Changed_Signature On_Changed_Dominance;

    FOn_Time_Updated_Signature On_Changed_Time_Game;
    FOn_Day_Updated_Signature On_Changed_Day;

private:
    void Handle_Changed_Sanity(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Empathy(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Fatigue(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &attribute_change_data);

    void Handle_Changed_Game_Over() const;
    void Handle_Changed_Game_Resumed() const;
    void Handle_Changed_Game_Menu_Paused() const;
    void Handle_Changed_Game_Demo_Completed() const;

    void Handle_Changed_Time_Game(const int32 hours, const int32 minutes, const int32 minutes_delta) const;
    void Handle_Changed_Day_Time(const int32 current_day) const;

    void Handle_Changed_Gameplay_Tag(const FGameplayTag gameplay_tag, const int32 new_count) const;


    UTLG_Attribute_Set *Get_TLG_Attribute_Set() const;

    float Prev_Sanity = -1.0f;
    float Prev_Empathy = -1.0f;
    float Prev_Fatigued = -1.0f;
    float Prev_Dominance = -1.0f;

};
//------------------------------------------------------------------------------------------------------------
