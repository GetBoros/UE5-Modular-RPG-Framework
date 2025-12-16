//------------------------------------------------------------------------------------------------------------
#include <Subsystems/GBC_Gameplay_Message_Subsystem.h>
//------------------------------------------------------------------------------------------------------------




// UGBC_Gameplay_Message_Subsystem
void UGBC_Gameplay_Message_Subsystem::Broadcast_Message(FGameplayTag event_tag, const UObject *payload)
{
    if (On_Event_Dispatched.IsBound() == true)
        On_Event_Dispatched.Broadcast(event_tag, payload);

    UE_LOG(LogTemp, Verbose, TEXT("EventBus: [%s] from %s"), *event_tag.ToString(), *GetNameSafe(payload) );

    if (On_Event_Dispatched.IsBound() == true)
        On_Event_Dispatched.Broadcast(event_tag, payload);  // Call in BP (Globaly, dificult to make in BP map with delegates)

    if (TSharedPtr<FGB_Native_Event_Delegate> *delegate_ptr = Listeners_Map.Find(event_tag) )
    {
        if (delegate_ptr->IsValid() == true)
            (*delegate_ptr)->Broadcast(event_tag, payload);
    }
}
//------------------------------------------------------------------------------------------------------------
FDelegateHandle UGBC_Gameplay_Message_Subsystem::Register_Listener(FGameplayTag event_tag, TFunction<void(FGameplayTag, const UObject *)> callback)
{
    TSharedPtr<FGB_Native_Event_Delegate> &delegate_ptr = Listeners_Map.FindOrAdd(event_tag);
    
    if (delegate_ptr.IsValid() != true)
        delegate_ptr = MakeShared<FGB_Native_Event_Delegate>();  // 2. Если его нет (nullptr) - создаем новый

    FDelegateHandle handle = delegate_ptr->AddLambda(callback);  // 3. Подписываемся Обрати внимание: AddLambda копирует твою TFunction, это нормально.

    return handle;
}
//------------------------------------------------------------------------------------------------------------
void UGBC_Gameplay_Message_Subsystem::Unregister_Listener(FGameplayTag event_tag, FDelegateHandle handle)
{
    if (TSharedPtr<FGB_Native_Event_Delegate> *delegate_ptr = Listeners_Map.Find(event_tag) )
    {
        if (delegate_ptr->IsValid() == true)
            (*delegate_ptr)->Remove(handle);
    }
}
//------------------------------------------------------------------------------------------------------------
