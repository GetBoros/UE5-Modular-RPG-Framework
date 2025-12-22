//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <UObject/Object.h>
#include <GBUI_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UAttributeSet;
//------------------------------------------------------------------------------------------------------------

UCLASS(Blueprintable, BlueprintType) class GBUI_API UGBUI_Widget_Controller : public UObject
{
    GENERATED_BODY()

public:
    virtual void Bind_Callbacks_To_Dependencies();  // Called to bind this controller to attribute changes in the AttributeSet
    UFUNCTION(BlueprintCallable) virtual void Broadcast_Initial_Values();  // Called after params are set to broadcast initial values to the widget
    UFUNCTION(BlueprintCallable) void Set_Widget_Controller_Params(APlayerController *pc, APlayerState *ps, UAbilitySystemComponent *asc, UAttributeSet *as);  // UI to set up the controller
    
protected:
    UPROPERTY(BlueprintReadOnly) TObjectPtr<APlayerController> Player_Controller;  // Pointers to the core gameplay objects
    UPROPERTY(BlueprintReadOnly) TObjectPtr<APlayerState> Player_State;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UAttributeSet> Attribute_Set;
};
//------------------------------------------------------------------------------------------------------------
