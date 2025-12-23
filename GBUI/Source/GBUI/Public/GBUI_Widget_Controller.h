//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <UObject/Object.h>
#include <GameplayEffectTypes.h>
#include <GBUI_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Attribute_Change_Signature, float, new_value);
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UAttributeSet;
class UGBG_Attribute_Set;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FController_Widget_Params
{
    GENERATED_BODY()

    FController_Widget_Params() {}
    FController_Widget_Params(APlayerController *pc, APlayerState *ps, UAbilitySystemComponent *asc, UAttributeSet *as)
     : Player_Controller(pc), Player_State(ps), Ability_System_Component(asc), Attribute_Set(as) 
    {

    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerController> Player_Controller = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> Player_State = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> Ability_System_Component = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAttributeSet> Attribute_Set = 0;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType) class GBUI_API UGBUI_Widget_Controller : public UObject
{
    GENERATED_BODY()

public:
    void On_Stamina_Changed_Callback(const FOnAttributeChangeData &data);

    UFUNCTION(BlueprintCallable, Category = "GBUI | Controller") void Set_Widget_Controller_Params(const FController_Widget_Params &params);
    UFUNCTION(BlueprintCallable, Category = "GBUI | Controller") void Bind_Callbacks_To_Dependencies();
    UFUNCTION(BlueprintCallable, Category = "GBUI | Controller") void Broadcast_Initial_Values();
    
    UPROPERTY(BlueprintAssignable, Category = "GBUI | Events") FOn_Attribute_Change_Signature On_Stamina_Changed;
    UPROPERTY(BlueprintReadOnly, Category = "GBUI | Data") TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(BlueprintReadOnly, Category = "GBUI | Data") TObjectPtr<const UGBG_Attribute_Set> Attribute_Set;
    
};
//------------------------------------------------------------------------------------------------------------
