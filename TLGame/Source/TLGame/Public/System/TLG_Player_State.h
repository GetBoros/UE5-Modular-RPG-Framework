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
struct FGameplayTag;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_State : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATLG_Player_State();

	virtual void BeginPlay();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	void Handle_Attribute_Sanity(float value) const;  // For test
	void Apply_Gameplay_Effect(const float value, const FGameplayTag &gameplay_tag_action, TSubclassOf<UGameplayEffect> gameplay_effect_class);

	UTLG_Attribute_Set* Get_Attribute_Set() const;

private:
	UFUNCTION() void Handle_Time_Advanced(int32 hours, int32 minutes, int32 minutes_delta);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UTLG_Attribute_Set> Attribute_Set;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<UGameplayEffect> Gameplay_Effect_Sanity_Class;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UGameplayEffect> Gameplay_Effect_Fatigue_Class;
	/*  0.069 (Ciborg 24h) | 0.104 (Norm 16h) | 0.138 (Weak 12h) | 0.208 (Sick 8h) || 0.1f - 16h - 960min - 96 Fatigue */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0")) float Fatigue_Accumulation_Rate = 0.105f;
};
//------------------------------------------------------------------------------------------------------------