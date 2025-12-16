//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "AbilitySystemInterface.h"

#include "GameFramework/Character.h"
#include "GBG_Player.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputComponent;
class UInputAction;
class UAbilitySystemComponent;
class UGBG_Attribute_Set;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Player : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGBG_Player();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController *new_controller) override; // <--- Важно для инициализации GAS на сервере
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

	UGBG_Attribute_Set *GetAttributeSet() const { return Attribute_Set; }

	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Look;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Jump;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true") ) UAbilitySystemComponent *Ability_System_Component;
	UPROPERTY() UGBG_Attribute_Set *Attribute_Set;
	
};
//------------------------------------------------------------------------------------------------------------
