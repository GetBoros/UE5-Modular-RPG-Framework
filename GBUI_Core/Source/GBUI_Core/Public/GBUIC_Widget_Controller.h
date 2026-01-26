//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Types/GBC_Attribute_Info.h>
#include <GameplayEffectTypes.h>
#include <GBUIC_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UGBC_Attribute_Info;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FController_Widget_Params
{
    GENERATED_BODY()
    
    FController_Widget_Params() { }
    FController_Widget_Params(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as, UGBC_Attribute_Info* info)
      : Player_Controller(pc), Player_State(ps), Ability_System_Component(asc), Attribute_Set(as), Attribute_Info(info) { }

    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerController> Player_Controller = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> Player_State = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> Ability_System_Component = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAttributeSet> Attribute_Set = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UGBC_Attribute_Info> Attribute_Info = 0;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType) class GBUI_CORE_API UGBUIC_Widget_Controller : public UObject  // !!! Platinum Standart
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable) void Init(const FController_Widget_Params &params);

    UFUNCTION(BlueprintCallable) virtual void Broadcast_Initial_Values();
    UFUNCTION(BlueprintCallable) virtual void Bind_Callbacks_To_Dependencies();

    UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerController> Player_Controller;
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<APlayerState> Player_State;
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UAttributeSet> Attribute_Set;
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController") TObjectPtr<UGBC_Attribute_Info> Attribute_Info;
    
};
//------------------------------------------------------------------------------------------------------------
