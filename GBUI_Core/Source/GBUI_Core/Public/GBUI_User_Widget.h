//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GBUI_User_Widget.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUI_Widget_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_CORE_API UGBUI_User_Widget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent) void On_Widget_Controller_Set();  // BP Event called when controller_widget setup
    
    UFUNCTION(BlueprintCallable) void Set_Widget_Controller(UGBUI_Widget_Controller *widget_controller);  // hud can send controller here
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UGBUI_Widget_Controller> Widget_Controller;
    
};
//------------------------------------------------------------------------------------------------------------
