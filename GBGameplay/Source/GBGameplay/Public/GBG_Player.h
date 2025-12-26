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
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent);

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

	UGBG_Attribute_Set *GetAttributeSet() const { return Attribute_Set; }

	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);
	void On_Jump_Bgn(const FInputActionValue &value);
	void On_Jump_End(const FInputActionValue &value);
	void On_Sprint_Bgn(const FInputActionValue &value);
	void On_Sprint_End(const FInputActionValue &value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Move = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Look = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Jump = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Sprint = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS") TSubclassOf<UGameplayEffect> Default_Attributes_Effect;  // GEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS") TArray<TSubclassOf<UGBG_Gameplay_Ability> > Default_Abilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true") ) UAbilitySystemComponent *Ability_System_Component = 0;
	UPROPERTY(VisibleAnywhere) UGBG_Attribute_Set *Attribute_Set;
	
};
//------------------------------------------------------------------------------------------------------------
