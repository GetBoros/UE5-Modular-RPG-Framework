//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>
#include <Data/TLG_Types.h>
#include <Interfaces/TLG_Interaction_Interface.h>

#include <TLG_Widget_Button.generated.h>
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UTLG_Data_Location;
class UTLG_Widget_Controller;
class UTLG_Widget_Tooltip;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button : public UGBUIC_User_Widget
{
    GENERATED_BODY()

public:
    virtual void NativeDestruct();
    virtual void NativeConstruct();
    virtual void On_Widget_Controller_Set_Implementation();
    virtual void Handle_Click();

    void Set_Button_Text(const FText &text_button) const;
    void Set_Button_Enabled(const bool is_enabled);

protected:
    TObjectPtr<UTLG_Widget_Controller> TLG_Widget_Controller;
    TObjectPtr<UTLG_Widget_Tooltip> TLG_Widget_Tooltip;

    UFUNCTION() void Handle_Click_Internal();
    UFUNCTION() void Handle_Hover_Internal();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Button;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;

    UPROPERTY(EditDefaultsOnly) TObjectPtr<USoundBase> Sound_Click;
    UPROPERTY(EditDefaultsOnly) TObjectPtr<USoundBase> Sound_Hover;

    UPROPERTY(EditDefaultsOnly) TSubclassOf<UTLG_Widget_Tooltip> TLG_Widget_Tooltip_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true) ) FText Text_Tooltip_Description;

};
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Action : public UTLG_Widget_Button
{
    GENERATED_BODY()

public:
    virtual void NativeDestruct();
    virtual void NativeConstruct();
    virtual void On_Widget_Controller_Set_Implementation();
    virtual void Handle_Click();

    void Init(const FTLG_Location_Action &action_data);

private:
    void Refresh_Button_State();

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
