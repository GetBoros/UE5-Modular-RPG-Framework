//------------------------------------------------------------------------------------------------------------
#include <Subsystems/GBC_Gameplay_Message_Subsystem.h>
//------------------------------------------------------------------------------------------------------------




// UGBC_Gameplay_Message_Subsystem
void UGBC_Gameplay_Message_Subsystem::Broadcast_Message(FGameplayTag event_tag, const UObject *payload)
{
    if (On_Event_Dispatched.IsBound() )
        On_Event_Dispatched.Broadcast(event_tag, payload);

    UE_LOG(LogTemp, Verbose, TEXT("EventBus: [%s] from %s"), *event_tag.ToString(), *GetNameSafe(payload) );

    if (On_Event_Dispatched.IsBound())  // 2. Потом кричим в Блюпринты (Глобально, так как в BP сложно сделать Map с делегатами)
        On_Event_Dispatched.Broadcast(event_tag, payload);

    if (TSharedPtr<FGB_Native_Event_Delegate> *delegate_ptr = Listeners_Map.Find(event_tag) )
    {
        if (delegate_ptr->IsValid() )
            (*delegate_ptr)->Broadcast(event_tag, payload);
    }
}
//------------------------------------------------------------------------------------------------------------
FDelegateHandle UGBC_Gameplay_Message_Subsystem::Register_Listener(FGameplayTag event_tag, TFunction<void(FGameplayTag, const UObject *)> callback)
{
    TSharedPtr<FGB_Native_Event_Delegate> &delegate_ptr = Listeners_Map.FindOrAdd(event_tag);
    
    if (!delegate_ptr.IsValid() )
        delegate_ptr = MakeShared<FGB_Native_Event_Delegate>();  // 2. Если его нет (nullptr) - создаем новый

    FDelegateHandle handle = delegate_ptr->AddLambda(callback);  // 3. Подписываемся Обрати внимание: AddLambda копирует твою TFunction, это нормально.

    return handle;
}
//------------------------------------------------------------------------------------------------------------
void UGBC_Gameplay_Message_Subsystem::Unregister_Listener(FGameplayTag event_tag, FDelegateHandle handle)
{
    if (TSharedPtr<FGB_Native_Event_Delegate> *delegate_ptr = Listeners_Map.Find(event_tag) )
    {
        if (delegate_ptr->IsValid() )
            (*delegate_ptr)->Remove(handle);
    }
}
//------------------------------------------------------------------------------------------------------------
