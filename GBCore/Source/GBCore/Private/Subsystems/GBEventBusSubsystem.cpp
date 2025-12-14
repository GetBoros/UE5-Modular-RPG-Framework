//------------------------------------------------------------------------------------------------------------
#include "Subsystems/GBEventBusSubsystem.h"
//------------------------------------------------------------------------------------------------------------




// UGBEventBusSubsystem
void UGBEventBusSubsystem::BroadcastEvent(FGameplayTag event_tag, const UObject *payload)
{
    if (OnEventDispatched.IsBound() )
        OnEventDispatched.Broadcast(event_tag, payload);

    UE_LOG(LogTemp, Verbose, TEXT("EventBus: [%s] from %s"), *event_tag.ToString(), *GetNameSafe(payload) );
}
//------------------------------------------------------------------------------------------------------------
