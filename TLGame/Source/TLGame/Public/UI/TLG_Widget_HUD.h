//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GameplayEffectTypes.h>
#include <TLG_Widget_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UTLG_Attribute_Set;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_HUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();

    void Init_GAS_Attributes();

    void Handle_Sanity_Changed(const FOnAttributeChangeData &data);
    void Handle_Dominance_Changed(const FOnAttributeChangeData &data);

    UFUNCTION(BlueprintImplementableEvent) void On_Sanity_Updated(float new_value, float max_value);
    UFUNCTION(BlueprintImplementableEvent) void On_Dominance_Updated(float new_value);

private:
    UPROPERTY() TObjectPtr<UAbilitySystemComponent> ASC;
    UPROPERTY() TObjectPtr<UTLG_Attribute_Set> Attribute_Set;
};
//------------------------------------------------------------------------------------------------------------
