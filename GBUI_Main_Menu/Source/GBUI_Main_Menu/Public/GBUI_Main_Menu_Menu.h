//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <GBUI_Main_Menu_Menu.generated.h>
//------------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UGBUI_Main_Menu_Button;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class GBUI_MAIN_MENU_API UGBUI_Main_Menu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();
    virtual void NativeConstruct();

    UFUNCTION(BlueprintCallable) void Temp();
    UFUNCTION(BlueprintCallable) void Test();

    // !!! TEMP Experimental
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UVerticalBox *VB_Button_Container;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UUserWidget *Button_New_Game;

};
//------------------------------------------------------------------------------------------------------------
