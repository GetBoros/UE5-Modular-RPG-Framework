//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <AbilitySystemInterface.h>
#include <GameFramework/Character.h>

#include <GBG_Player.generated.h>
//------------------------------------------------------------------------------------------------------------
class UInputComponent;
class UInputAction;
class UAbilitySystemComponent;
class UGameplayEffect;
class UGBG_Attribute_Set;
class UGBG_Gameplay_Ability;
class UGBG_Destructible_Interaction;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Player : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGBG_Player();
	
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void PossessedBy(AController *new_controller);
	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component);

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

	UGBG_Attribute_Set *GetAttributeSet() const;

private:
	void On_Move(const FInputActionValue &value);
	void On_Look(const FInputActionValue &value);
	void On_Jump_Bgn(const FInputActionValue &value);
	void On_Jump_End(const FInputActionValue &value);
	void On_Sprint_Bgn(const FInputActionValue &value);
	void On_Sprint_End(const FInputActionValue &value);
	void On_Interact(const FInputActionValue &value);

	mutable UAbilitySystemComponent *Ability_System_Component;
	UGBG_Attribute_Set *Attribute_Set;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UInputAction *Action_Move = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UInputAction *Action_Look = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UInputAction *Action_Jump = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UInputAction *Action_Sprint = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UInputAction *Action_Interact = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UGameplayEffect> Default_Attributes_Effect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TArray<TSubclassOf<UGBG_Gameplay_Ability> > Default_Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) UGBG_Destructible_Interaction* Destructible_Interaction_Component;

};
//------------------------------------------------------------------------------------------------------------
