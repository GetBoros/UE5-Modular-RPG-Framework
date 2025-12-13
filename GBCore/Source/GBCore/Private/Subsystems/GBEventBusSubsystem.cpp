//------------------------------------------------------------------------------------------------------------
#include "Subsystems/GBEventBusSubsystem.h"
//------------------------------------------------------------------------------------------------------------




// UGBEventBusSubsystem
void UGBEventBusSubsystem::BroadcastEvent(FGameplayTag EventTag, const UObject* Payload)
{
    if (OnEventDispatched.IsBound() )
        OnEventDispatched.Broadcast(EventTag, Payload);

    UE_LOG(LogTemp, Verbose, TEXT("EventBus: [%s] from %s"), *EventTag.ToString(), *GetNameSafe(Payload) );
}
//------------------------------------------------------------------------------------------------------------
