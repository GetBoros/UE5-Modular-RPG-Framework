//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <Data/TLG_Data_Location.h>

#include <TLG_Widget_Button_Navigation.generated.h>
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

protected:
    UFUNCTION() void Handle_Click_Internal();

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Location_Name;
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

    int32 Time_Cost_Minutes = 0;
    FGameplayTag Gameplay_Tag_Action;
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
