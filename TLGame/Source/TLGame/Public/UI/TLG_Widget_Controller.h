//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_Widget_Controller.h>

#include <TLG_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOn_Attribute_Changed_Signature, float, new_value, float, delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOn_Time_Updated_Signature, int32, hours, int32, minutes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Day_Updated_Signature, int32, current_day);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Over);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Resumed);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Menu_Paused);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Demo_Completed);
//------------------------------------------------------------------------------------------------------------
class UTLG_Attribute_Set;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Controller : public UGBUIC_Widget_Controller
{
    GENERATED_BODY()

public:
    virtual void Broadcast_Initial_Values();
    virtual void Bind_Callbacks_To_Dependencies();

    UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Signature On_Changed_Sanity;
    UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Signature On_Changed_Fatigued;
    UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Signature On_Changed_Dominance;
    UPROPERTY(BlueprintAssignable) FOn_Time_Updated_Signature On_Changed_Time_Game;
    UPROPERTY(BlueprintAssignable) FOn_Day_Updated_Signature On_Changed_Day;

    mutable FOn_Game_Over On_Game_Over;
    mutable FOn_Game_Resumed On_Game_Resumed;
    mutable FOn_Game_Menu_Paused On_Game_Menu_Paused;
    mutable FOn_Game_Demo_Completed On_Game_Demo_Completed;

private:
    void Handle_Changed_Sanity(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Fatigue(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &attribute_change_data);
    void Handle_Changed_Game_Over();
    void Handle_Changed_Game_Resumed();
    void Handle_Changed_Game_Menu_Paused();
    void Handle_Changed_Game_Demo_Completed();

    UTLG_Attribute_Set *Get_TLG_Attribute_Set() const;

    float Prev_Sanity = -1.0f;
    float Prev_Fatigued = -1.0f;
    float Prev_Dominance = -1.0f;

    UFUNCTION() void Handle_Changed_Time_Game(int32 hours, int32 minutes, int32 minutes_delta);
    UFUNCTION() void Handle_Changed_Day_Time(int32 current_day);

};
//------------------------------------------------------------------------------------------------------------
