//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <GBUIC_User_Widget.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUIC_Widget_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_CORE_API UGBUIC_User_Widget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent) void On_Widget_Controller_Set();  // BP Event called when controller_widget setup
    
    UFUNCTION(BlueprintCallable) void Set_Widget_Controller(UGBUIC_Widget_Controller *widget_controller);  // hud can send controller here
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UGBUIC_Widget_Controller> Widget_Controller;
    
};
//------------------------------------------------------------------------------------------------------------
