//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>

#include <TLG_Player_State.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Attribute_Set;
class UGameplayEffect;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_State : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ATLG_Player_State();

    virtual void BeginPlay();
    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

    UTLG_Attribute_Set *Get_Attribute_Set() const;

private:
    UFUNCTION() void Handle_Time_Advanced(int32 hours, int32 minutes, int32 minutes_delta);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Attribute_Set> Attribute_Set;

    UPROPERTY(EditDefaultsOnly) TSubclassOf<UGameplayEffect> Gameplay_Effect_Fatigue_Class;
};
//------------------------------------------------------------------------------------------------------------