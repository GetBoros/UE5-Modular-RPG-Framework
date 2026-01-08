//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>
#include <GameplayTagContainer.h>

#include <TLG_Player_State.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UTLG_Attribute_Set;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_State : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ATLG_Player_State();

    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable) UTLG_Attribute_Set *Get_Attribute_Set() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY() TObjectPtr<UTLG_Attribute_Set> Attribute_Set;

};
//------------------------------------------------------------------------------------------------------------