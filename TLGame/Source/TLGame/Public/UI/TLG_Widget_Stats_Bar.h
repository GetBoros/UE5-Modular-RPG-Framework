//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <TLG_Widget_Stats_Bar.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Stat;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Stats_Bar : public UGBUIC_User_Widget
{
	GENERATED_BODY()
	
public:
    virtual void On_Widget_Controller_Set_Implementation();

    UFUNCTION() void Update_Sanity(float new_value, float delta);
    UFUNCTION() void Update_Empathy(float new_value, float delta);
    UFUNCTION() void Update_Fatigued(float new_value, float delta);
    UFUNCTION() void Update_Dominance(float new_value, float delta);

private:
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Sanity;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Empathy;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Fatigued;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Dominance;

};
//------------------------------------------------------------------------------------------------------------
