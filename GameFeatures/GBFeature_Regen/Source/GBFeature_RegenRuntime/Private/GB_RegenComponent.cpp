#include "GB_RegenComponent.h"
#include "GBAI_Library.h" // Подключаем твою библиотеку логгера

UGB_RegenComponent::UGB_RegenComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickInterval = 1.0f; // Тикаем раз в секунду
}

void UGB_RegenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UGBAI_Library::Log_GB_Event("Regen Feature: Healing +5 HP on " + GetOwner()->GetName());
}