//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h" // Живет всю игру, даже при смене уровней
#include "GameplayTagContainer.h"
#include "GBEventBusSubsystem.generated.h"
//------------------------------------------------------------------------------------------------------------
// Объявляем делегат. Payload (полезная нагрузка) может быть UObject* или struct.
// Для простоты передадим Актора-инициатора и опциональные параметры.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGBGameEventDelegate, FGameplayTag, EventTag, const UObject*, Payload);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBEventBusSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Отправить событие (Fire & Forget)
    UFUNCTION(BlueprintCallable, Category = "EventBus")
    void BroadcastEvent(FGameplayTag EventTag, const UObject* Payload = nullptr);

    // Подписаться на событие (C++ версия)
    // Возвращаем хендл, чтобы можно было отписаться
    FDelegateHandle RegisterListener(FGameplayTag EventTag, const TFunction<void(FGameplayTag, const UObject*)>& Callback);

    // Отписаться
    void UnregisterListener(FGameplayTag EventTag, FDelegateHandle Handle);

private:
    // Словарь: Тег события -> Список подписчиков (C++ native delegates)
    // Для Blueprints реализация сложнее (нужен Map с Dynamic Delegates),
    // но для C++ TMap<Tag, MulticastDelegate> - идеально.

    // Упрощенный вариант для примера (общий бродкаст):
    UPROPERTY(BlueprintAssignable, Category = "EventBus")
    FGBGameEventDelegate OnEventDispatched;
};
//------------------------------------------------------------------------------------------------------------
