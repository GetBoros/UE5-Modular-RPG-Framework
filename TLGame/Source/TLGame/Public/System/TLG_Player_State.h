//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>
#include <GameplayTagContainer.h>

#include <TLG_Player_State.generated.h>
//------------------------------------------------------------------------------------------------------------
class UGBC_Attribute_Info;
class UTLG_Attribute_Set;
class UGameplayEffect;
class UAbilitySystemComponent;

struct FGameplayTagContainer;
struct FGameplayAttribute;
struct FGameplayTag;
struct FTLG_Location_Action;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_State : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATLG_Player_State();

	virtual void BeginPlay();
	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const;

	UTLG_Attribute_Set *Get_Attribute_Set() const;
	FGameplayAttribute Get_Attribute_By_Tag(const FGameplayTag &gameplay_tag_attribute) const;

	void Apply_Multy_Dynamic_Change(const FTLG_Location_Action &tlg_location_action);  // !!! TEMP
	void Apply_Dynamic_Change(float magnitude, FGameplayTag attribute_tag);

private:
	void Handle_Sanity_Zero();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Attribute_Set> Attribute_Set;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UGBC_Attribute_Info> GBC_Attribute_Info;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UGameplayEffect> Gameplay_Effect_Class_Attributes;
	/*  0.069 (Ciborg 24h) | 0.104 (Norm 16h) | 0.138 (Weak 12h) | 0.208 (Sick 8h) || 0.1f - 16h - 960min - 96 Fatigue */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0") ) float Fatigue_Accumulation_Rate = 0.105f;
};
//------------------------------------------------------------------------------------------------------------