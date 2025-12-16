//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Subsystems/GameInstanceSubsystem.h>
#include <GameplayTagContainer.h>
#include <GBC_Gameplay_Message_Subsystem.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE_TwoParams(FGB_Native_Event_Delegate, FGameplayTag, const UObject *);  // For C++ faster then dynamic
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGBGameEventDelegate, FGameplayTag, event_tag, const UObject *, payload);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBC_Gameplay_Message_Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "EventBus") void Broadcast_Message(FGameplayTag event_tag, const UObject *payload);  // Send event fire and forgot

    FDelegateHandle Register_Listener(FGameplayTag event_tag, TFunction<void(FGameplayTag, const UObject *)> callback);
    void Unregister_Listener(FGameplayTag event_tag, FDelegateHandle handle);

    UPROPERTY(BlueprintAssignable, Category = "EventBus") FGBGameEventDelegate On_Event_Dispatched;  // !!! TEMP EXAMPLE

private:
    TMap<FGameplayTag, TSharedPtr<FGB_Native_Event_Delegate>> Listeners_Map;  // !!! TEMP EXAMPLE

};
//------------------------------------------------------------------------------------------------------------
