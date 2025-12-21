//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Abilities/Tasks/AbilityTask.h>
#include <AttributeSet.h>
#include <GBG_AT_Wait_Attribute_Change.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOn_Attribute_Changed_Delegate, float, new_value, float, old_value);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_AT_Wait_Attribute_Change : public UAbilityTask
{
	GENERATED_BODY()

public:
	// Factory Method. Creates the node in Blueprints
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "owning_ability", DefaultToSelf = "owning_ability", BlueprintInternalUseOnly = "true") )
	static UGBG_AT_Wait_Attribute_Change *Wait_For_Attribute_Drop(UGameplayAbility *owning_ability, FGameplayAttribute attribute, float threshold);

	virtual void Activate();  // Called when the task starts (node activation)
	virtual void OnDestroy(bool ability_ended);  // Cleanup when task ends

	UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Delegate On_Threshold_Reached;  // Blueprint output execution pin

protected:
	void On_Attribute_Change_Callback(const FOnAttributeChangeData &data);  // Internal callback called when the attribute changes

	float Threshold_Value;
	FGameplayAttribute Attribute_To_Listen;
	FDelegateHandle Delegate_Handle;
};
//------------------------------------------------------------------------------------------------------------