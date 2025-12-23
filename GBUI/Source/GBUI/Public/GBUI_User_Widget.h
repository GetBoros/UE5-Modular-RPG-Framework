//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GBUI_User_Widget.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBUI_Widget_Controller;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_API UGBUI_User_Widget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "GBUI | Widget") void On_Widget_Controller_Set();  // BP Event called when controller_widget setup
    
    UFUNCTION(BlueprintCallable, Category = "GBUI | Widget") void Set_Widget_Controller(UObject *in_controller);  // hud can send controller here
    
    UPROPERTY(BlueprintReadOnly, Category = "GBUI | Widget") TObjectPtr<UGBUI_Widget_Controller> Widget_Controller;
    
};
//------------------------------------------------------------------------------------------------------------
