//------------------------------------------------------------------------------------------------------------
#include <GB_RegenComponent.h>
#include <GBAI_Library.h>
//------------------------------------------------------------------------------------------------------------




// UGB_RegenComponent
UGB_RegenComponent::UGB_RegenComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickInterval = 1.0f;  // Tick one per seconds
}
//------------------------------------------------------------------------------------------------------------
void UGB_RegenComponent::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function)
{
    Super::TickComponent(delta_time, tick_type, this_tick_function);

    UGBAI_Library::Log_GB_Event("Regen Feature: Healing +5 HP on " + GetOwner()->GetName() );
}
//------------------------------------------------------------------------------------------------------------
