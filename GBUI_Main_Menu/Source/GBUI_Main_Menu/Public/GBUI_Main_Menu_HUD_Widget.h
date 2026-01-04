//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_User_Widget.h>

#include <GBUI_Main_Menu_HUD_Widget.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUI_Main_Menu;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class GBUI_MAIN_MENU_API UGBUI_Main_Menu_HUD_Widget : public UGBUIC_User_Widget
{
	GENERATED_BODY()

public:
    virtual void NativePreConstruct();
    virtual void NativeConstruct();

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget) ) UGBUI_Main_Menu *Menu_Main;

};
//------------------------------------------------------------------------------------------------------------
