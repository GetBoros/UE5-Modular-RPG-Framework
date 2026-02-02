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
UCLASS() class TLGAME_API UTLG_Widget_Button_Navigation : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct();

    void Init(const FTLG_Location_Exit &tlg_location_exit);
    void Init_Temp(const FTLG_Location_Action &tlg_location_action);

private:
    FText Format_Time_From_Minutes(int32 minutes_cost) const;

    UFUNCTION() void Handle_Click();
    
    UPROPERTY() TObjectPtr<UTLG_Data_Location> Target_Location;
    
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> TB_Loction_Name;
};
//------------------------------------------------------------------------------------------------------------
