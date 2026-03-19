//------------------------------------------------------------------------------------------------------------
#include <System/GBG_Player_State.h>

#include <GAS/GBG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Player_State
AGBG_Player_State::AGBG_Player_State()
{
    Attribute_Set_Default = CreateDefaultSubobject<UGBG_Attribute_Set>(TEXT("Attribute_Set_Default") );
    Ability_System_Component = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability_System_Component") );
    
    if (Ability_System_Component == 0)
        return;

    Ability_System_Component->SetIsReplicated(true);
    Ability_System_Component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Player_State::BeginPlay()
{
    Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *AGBG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
UGBG_Attribute_Set *AGBG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set_Default;
}
//------------------------------------------------------------------------------------------------------------
