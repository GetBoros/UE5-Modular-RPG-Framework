//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "AbilitySystemInterface.h"

#include "GameFramework/Character.h"
#include "GBG_Player.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputComponent;
class UInputAction;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API AGBG_Player : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGBG_Player();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Look;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Action_Jump;
	
};
//------------------------------------------------------------------------------------------------------------
