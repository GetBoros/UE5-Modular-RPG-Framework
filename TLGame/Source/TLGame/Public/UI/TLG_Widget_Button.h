//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>
#include <Data/TLG_Data_Location.h>
#include <Interfaces/TLG_Interaction_Interface.h>

#include <TLG_Widget_Button.generated.h>
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UTLG_Data_Location;
class UTLG_Widget_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button : public UGBUIC_User_Widget
{
    GENERATED_BODY()

public:
    virtual void NativeDestruct();
    virtual void NativeConstruct();
    virtual void Handle_Click();
    virtual void On_Widget_Controller_Set_Implementation();

    void Set_Button_Text(const FText &text_button) const;
    void Set_Button_Enabled(const bool is_enabled);

protected:
    UTLG_Widget_Controller *TLG_Widget_Controller;

    UFUNCTION() void Handle_Click_Internal();
    UFUNCTION() void Handle_Hover_Internal();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Button;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;

    UPROPERTY(EditDefaultsOnly) TObjectPtr<USoundBase> Sound_Click;
    UPROPERTY(EditDefaultsOnly) TObjectPtr<USoundBase> Sound_Hover;
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Action : public UTLG_Widget_Button
{
    GENERATED_BODY()

public:
    virtual void NativeDestruct();
    virtual void Handle_Click();
    virtual void On_Widget_Controller_Set_Implementation();

    void Init(const FTLG_Location_Action &action_data);

private:
    UFUNCTION() void Refresh_Button_State();

    FText Format_Time_From_Minutes(int32 minutes_cost) const;  // !!! TEMP || Can be helpful

    FTLG_Location_Action TLG_Location_Action;
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Navigation : public UTLG_Widget_Button
{
	GENERATED_BODY()
	
public:
    virtual void Handle_Click();

    void Init(const FTLG_Location_Exit &tlg_location_exit);

private:
    UPROPERTY() TObjectPtr<UTLG_Data_Location> Target_Location;
    
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Flow : public UTLG_Widget_Button
{
	GENERATED_BODY()
	
public:
    virtual void Handle_Click();

    void Init(const ETLG_Game_Flow_Option tlg_game_flow_option, const FText &text_button);

private:
    ETLG_Game_Flow_Option TLG_Game_Flow_Option;

};
//------------------------------------------------------------------------------------------------------------
