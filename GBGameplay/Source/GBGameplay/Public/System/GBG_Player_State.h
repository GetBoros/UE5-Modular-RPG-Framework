//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>

#include <GBG_Player_State.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBG_Attribute_Set;
class UGBG_Ability_Set;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Player_State : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AGBG_Player_State();

	virtual void BeginPlay();
	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBG_Attribute_Set> Attribute_Set_Default;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBG_Ability_Set> GBG_Ability_Set;
};
//------------------------------------------------------------------------------------------------------------

