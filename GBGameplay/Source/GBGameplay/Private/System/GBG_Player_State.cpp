//------------------------------------------------------------------------------------------------------------
#include <System/GBG_Player_State.h>

#include <GAS/GBG_Attribute_Set.h>
#include <GAS/Data/GBG_GAS_Defaults_Init.h>

#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Player_State
AGBG_Player_State::AGBG_Player_State()
{
    Attribute_Set_Default = CreateDefaultSubobject<UGBG_Attribute_Set>(TEXT("Attribute_Set_Default") );
    
    Ability_System_Component = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability_System_Component") );
    Ability_System_Component->SetIsReplicated(true);
    Ability_System_Component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player_State::BeginPlay()
{
    Super::BeginPlay();

    if (ensureMsgf(GBG_Ability_Set, TEXT("Auto add standart abilities and effects, data driven") ) )
        GBG_Ability_Set->Grant_To_Ability_System(Ability_System_Component, this);  // Apply abilities and passive effects
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *AGBG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
