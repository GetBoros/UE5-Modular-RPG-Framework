//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <Data/TLG_Data_Location.h>
#include <Interfaces/TLG_Interaction_Interface.h>

#include <TLG_Widget_Button.generated.h>
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UTLG_Data_Location;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();
    virtual void Handle_Click();

    void Set_Button_Text(const FText &text_button) const;

protected:
    UFUNCTION() void Handle_Click_Internal();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Button;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Action : public UTLG_Widget_Button
{
    GENERATED_BODY()

public:
    virtual void Handle_Click();
    
    void Init(const FTLG_Location_Action &action_data);

private:
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
