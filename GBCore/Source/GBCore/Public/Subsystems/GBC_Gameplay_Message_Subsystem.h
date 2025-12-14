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
    UFUNCTION(BlueprintCallable, Category = "EventBus") void Broadcast_Message(FGameplayTag EventTag, const UObject* Payload = nullptr);  // Send event fire and forgot

    FDelegateHandle Register_Listener(FGameplayTag event_tag, TFunction<void(FGameplayTag, const UObject *)> callback);
    void Unregister_Listener(FGameplayTag event_tag, FDelegateHandle handle);

    UPROPERTY(BlueprintAssignable, Category = "EventBus") FGBGameEventDelegate On_Event_Dispatched;  // !!! TEMP EXAMPLE

private:
    TMap<FGameplayTag, TSharedPtr<FGB_Native_Event_Delegate>> Listeners_Map;  // !!! TEMP EXAMPLE

};
//------------------------------------------------------------------------------------------------------------



#pragma region HELP
//
/*
✅ Plus (When good):
    Полная развязка модулей: GBUI не зависит от GBAI. Оба зависят только от GBCore и Тегов.
    Легкость расширения: Хочешь добавить звук при голоде? Просто создай класс HungerAudioPlayer, подпишись на событие. Не надо лезть в код персонажа.
    Простота тестирования: Ты можешь вызвать событие Game.Event.HungerChanged из консоли или чит-менеджера, и UI обновится. Тебе не нужно реально морить персонажа голодом.

❌ Minus (Danger):
    Spaghetti Flow (Потеря контроля): Когда ты смотришь код UpdateHunger, ты не видишь явного вызова Widget->Update(). Ты видишь Broadcast. Чтобы понять, что произойдет дальше, тебе нужно искать по всему проекту "Кто подписан на этот тег?". Это усложняет отладку.
    Производительность: Если посылать события каждый кадр (Tick) — это убьет FPS. Event Bus только для разовых событий (умер, получил урон, съел, лвл-ап).
    Типизация: Передача данных через UObject* Payload или struct требует кастов (Cast), что может быть неудобно.

*/
#pragma endregion
