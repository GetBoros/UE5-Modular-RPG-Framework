//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUI_Widget_Controller.h>
#include <GBUI_HUD_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, new_value);  // This is the "phone line" signature for sending data to widgets. It declares a delegate that takes one float parameter.
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_API UGBUI_HUD_Widget_Controller : public UGBUI_Widget_Controller
{
    GENERATED_BODY()

public:
    virtual void Broadcast_Initial_Values();
    virtual void Bind_Callbacks_To_Dependencies();
    
    UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature On_Health_Changed;  // Delegates that Widgets can bind to, to receive updates.
    UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature On_Max_Health_Changed;
    UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature On_Stamina_Changed;
    UPROPERTY(BlueprintAssignable) FOnAttributeChangedSignature On_Max_Stamina_Changed;

protected:
    void Health_Changed(const struct FOnAttributeChangeData& data);  // Callback functions that will be bound to GAS attribute change events.
    void Max_Health_Changed(const struct FOnAttributeChangeData& data);
    void Stamina_Changed(const struct FOnAttributeChangeData& data);
    void Max_Stamina_Changed(const struct FOnAttributeChangeData& data);
};
//------------------------------------------------------------------------------------------------------------
