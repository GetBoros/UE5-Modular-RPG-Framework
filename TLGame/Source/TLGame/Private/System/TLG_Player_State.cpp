//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Player_State.h>
#include <System/TLG_Game_State.h>
#include <Data/TLG_Data_Gameplay_Tags.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <GameplayTagContainer.h>
#include <AbilitySystemComponent.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Player_State
ATLG_Player_State::ATLG_Player_State()
{
    Attribute_Set = CreateDefaultSubobject<UTLG_Attribute_Set>(TEXT("Attribute_Set") );
    Ability_System_Component = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability_System_Component") );
    
    if (Ability_System_Component == 0)
        return;

    Ability_System_Component->SetIsReplicated(true);
    Ability_System_Component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::BeginPlay()
{
    Super::BeginPlay();

    // if (ATLG_Game_State *tlg_game_state = GetWorld()->GetGameState<ATLG_Game_State>() )
    //     tlg_game_state->On_Updated_Time.AddDynamic(this, &ATLG_Player_State::Handle_Time_Advanced);
}
//------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent *ATLG_Player_State::GetAbilitySystemComponent() const
{
    return Ability_System_Component;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Player_State::Apply_Dynamic_Change(float value, FGameplayTag attribute_tag)
{
    float result;
    FGameplayTag gameplay_tag;

    gameplay_tag = attribute_tag;
    if (Gameplay_Effect_Class_Attributes == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("TLG_Player_State: ASC or Default GE is missing!"));
        return;
    }

    if (gameplay_tag.MatchesTag(FTLG_Data_Gameplay_Tags::Get().Action_System_Computer) )
    {
        result = static_cast<float>(value) * Fatigue_Accumulation_Rate;
        gameplay_tag = FTLG_Data_Gameplay_Tags::Get().Attribut_Player_Fatigued;
    }
    else
        result = value;

    // 1. Создаем контекст эффекта
    FGameplayEffectContextHandle context_handle = Ability_System_Component->MakeEffectContext();
    context_handle.AddSourceObject(this);

    // 2. Создаем Spec (экземпляр эффекта, готовый к применению)
    const FGameplayEffectSpecHandle spec_handle = Ability_System_Component->MakeOutgoingSpec(Gameplay_Effect_Class_Attributes, 1.0f, context_handle);

    if (spec_handle.IsValid() )
    {
        // 3. --- SET BY CALLER MAGIC --- Назначаем значение (result) для конкретного тега (gameplay_tag)
        spec_handle.Data->SetSetByCallerMagnitude(gameplay_tag, result);

        // 4. Применяем
        Ability_System_Component->ApplyGameplayEffectSpecToSelf(*spec_handle.Data.Get() );
    }
}
//------------------------------------------------------------------------------------------------------------
UTLG_Attribute_Set *ATLG_Player_State::Get_Attribute_Set() const
{
    return Attribute_Set;
}
//------------------------------------------------------------------------------------------------------------
