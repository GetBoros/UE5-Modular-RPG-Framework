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

    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Sanity(const float sanity_curr, const float sanity_max);
    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Dominance(const float dominance_curr);

private:
    void Handle_Changed_Sanity(const FOnAttributeChangeData &data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &data);

    UPROPERTY() TObjectPtr<UAbilitySystemComponent> ASC;
    UPROPERTY() TObjectPtr<UTLG_Attribute_Set> Attribute_Set;
};
//------------------------------------------------------------------------------------------------------------
