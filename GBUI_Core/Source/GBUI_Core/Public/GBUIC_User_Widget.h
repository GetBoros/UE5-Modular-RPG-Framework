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
    UFUNCTION(BlueprintNativeEvent) void On_Widget_Controller_Set();
    virtual void On_Widget_Controller_Set_Implementation();
    
    UFUNCTION(BlueprintCallable) void Set_Widget_Controller(UGBUIC_Widget_Controller *gbuic_widget_controller);  // hud can send controller here

    UPROPERTY(BlueprintReadOnly) TObjectPtr<UGBUIC_Widget_Controller> GBUIC_Widget_Controller;
    
};
//------------------------------------------------------------------------------------------------------------
