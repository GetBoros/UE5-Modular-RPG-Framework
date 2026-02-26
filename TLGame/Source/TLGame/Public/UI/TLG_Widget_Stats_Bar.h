//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <TLG_Widget_Stats_Bar.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UHorizontalBox;
class UVerticalBox;
class UTLG_Widget_Stat;
class UTLG_Widget_Text_Floating;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Stats_Bar : public UGBUIC_User_Widget
{
	GENERATED_BODY()
	
public:
    virtual void On_Widget_Controller_Set_Implementation();

private:
    void Spawn_Text_Floating(const float delta, const FText &name_text);  // Spawn in VB_Text_Floating_Events container || Move to UTLG_Widget_Stats_Bar?
    
    void Update_Sanity(float new_value, float delta);
    void Update_Empathy(float new_value, float delta);
    void Update_Fatigued(float new_value, float delta);
    void Update_Dominance(float new_value, float delta);

    void Update_Day(int32 current_day);
    void Update_Time_Game(int32 hours, int32 minutes);

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Sanity;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Empathy;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Fatigued;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Stat> TLG_Widget_Stat_Dominance;

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_Clock;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_Day_Counter;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Text_Floating> TLG_Widget_Text_Floating_Class;
   
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Text_Floating_Events;

};
//------------------------------------------------------------------------------------------------------------
