//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "GBEventBusSubsystem.generated.h"
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGBGameEventDelegate, FGameplayTag, event_tag, const UObject *, payload);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBEventBusSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "EventBus") void BroadcastEvent(FGameplayTag EventTag, const UObject* Payload = nullptr);  // Send event fire and forgot

    FDelegateHandle RegisterListener(FGameplayTag event_tag, const TFunction<void(FGameplayTag, const UObject *)> &callback);  // Sub for event and return handle for unsub

    void UnregisterListener(FGameplayTag EventTag, FDelegateHandle Handle);  // Unsub

    // Словарь: Тег события -> Список подписчиков (C++ native delegates)
    // Для Blueprints реализация сложнее (нужен Map с Dynamic Delegates),
    // но для C++ TMap<Tag, MulticastDelegate> - идеально.

    UPROPERTY(BlueprintAssignable, Category = "EventBus") FGBGameEventDelegate OnEventDispatched;  // Example
};
//------------------------------------------------------------------------------------------------------------
