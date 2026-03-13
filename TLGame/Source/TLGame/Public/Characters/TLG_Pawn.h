//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/Pawn.h>
#include <AbilitySystemInterface.h>

#include <TLG_Pawn.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class ATLG_Player_State;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Pawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATLG_Pawn();

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	virtual void PossessedBy(AController* new_controller);
	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

private:
	mutable UAbilitySystemComponent *Ability_System_Component;
};
//------------------------------------------------------------------------------------------------------------
