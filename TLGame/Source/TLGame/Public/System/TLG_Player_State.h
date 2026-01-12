//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>

#include <TLG_Player_State.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Attribute_Set;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_State : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ATLG_Player_State();

    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

    UFUNCTION(BlueprintCallable) UTLG_Attribute_Set *Get_Attribute_Set() const;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Attribute_Set> Attribute_Set;

};
//------------------------------------------------------------------------------------------------------------