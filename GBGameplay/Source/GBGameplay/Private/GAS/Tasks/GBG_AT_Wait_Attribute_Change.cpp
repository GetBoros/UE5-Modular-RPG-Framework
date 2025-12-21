//------------------------------------------------------------------------------------------------------------
#include <GAS/Tasks/GBG_AT_Wait_Attribute_Change.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// UGBG_AT_Wait_Attribute_Change
UGBG_AT_Wait_Attribute_Change *UGBG_AT_Wait_Attribute_Change::Wait_For_Attribute_Drop(UGameplayAbility *owning_ability, FGameplayAttribute attribute, float threshold)
{
	UGBG_AT_Wait_Attribute_Change *my_task = NewAbilityTask<UGBG_AT_Wait_Attribute_Change>(owning_ability);  // Create new tasks instance

	my_task->Attribute_To_Listen = attribute;  // Cache parameters
	my_task->Threshold_Value = threshold;

	return my_task;
}
//------------------------------------------------------------------------------------------------------------
void UGBG_AT_Wait_Attribute_Change::Activate()
{
	Super::Activate();

	if (AbilitySystemComponent == 0)
		return;

	// Check if the value is already at or below the threshold
	const float current_value = AbilitySystemComponent->GetNumericAttribute(Attribute_To_Listen);
	if (current_value <= Threshold_Value)
	{
		if (ShouldBroadcastAbilityTaskDelegates() )
			On_Threshold_Reached.Broadcast(current_value, current_value);
		
		EndTask();  // End task imediatly
		
		return;
	}

	// Otherwise, subscribe to attribute changes
	Delegate_Handle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute_To_Listen).AddUObject(this, &UGBG_AT_Wait_Attribute_Change::On_Attribute_Change_Callback);
}
//------------------------------------------------------------------------------------------------------------
void UGBG_AT_Wait_Attribute_Change::On_Attribute_Change_Callback(const FOnAttributeChangeData& data)
{// Callback triggered whenever the attribute changes (e.g., Stamina decreases)
	
	if (data.NewValue <= Threshold_Value)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
			On_Threshold_Reached.Broadcast(data.NewValue, data.OldValue);
		
		EndTask();  // End task if value is lower than threshold
	}
}
//------------------------------------------------------------------------------------------------------------
void UGBG_AT_Wait_Attribute_Change::OnDestroy(bool ability_ended)
{
	if (AbilitySystemComponent != 0 && Delegate_Handle.IsValid() )  // Unsubscribe from the delegate to prevent crashes
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute_To_Listen).Remove(Delegate_Handle);

	Super::OnDestroy(ability_ended);
}
//------------------------------------------------------------------------------------------------------------