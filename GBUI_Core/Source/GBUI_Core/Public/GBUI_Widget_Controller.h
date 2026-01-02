//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Types/GBC_Attribute_Info.h>
#include <GameplayEffectTypes.h>
#include <GBUI_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Attribute_Change_Signature, float, new_value);
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UGBC_Attribute_Info;
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FController_Widget_Params
{
    GENERATED_BODY()

    FController_Widget_Params() { }
    FController_Widget_Params(APlayerController *pc, APlayerState *ps, UAbilitySystemComponent *asc, UGBC_Attribute_Info *attribute_info)
     : Player_Controller(pc), Player_State(ps), Ability_System_Component(asc), Attribute_Info_Asset(attribute_info) { }

    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerController> Player_Controller = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<APlayerState> Player_State = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> Ability_System_Component = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UGBC_Attribute_Info> Attribute_Info_Asset = 0;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType) class GBUI_CORE_API UGBUI_Widget_Controller : public UObject
{
    GENERATED_BODY()

public:
    UGBUI_Widget_Controller();

    void Init(const FController_Widget_Params &params);
    void Broadcast_Initial_Values();
    
protected:
    UPROPERTY(BlueprintAssignable) FOn_Attribute_Change_Signature On_Stamina_Changed;  // Can bind from BP
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UGBC_Attribute_Info> Attribute_Info;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTag Stamina_Tag;

private:
    void Bind_Callbacks_To_Dependencies();
    void On_Stamina_Changed_Callback(const FOnAttributeChangeData &data);

    FGBC_Attribute_Info_Item Attribute_Info_Stamina;

};
//------------------------------------------------------------------------------------------------------------
