//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <NativeGameplayTags.h>
//------------------------------------------------------------------------------------------------------------
struct FTLG_Data_Gameplay_Tags
{
public:
    static void Initialize_Native_Tags();
    
    static const FTLG_Data_Gameplay_Tags &Get();

    // Portrait Tags
    FGameplayTag Portrait_Happy;
    FGameplayTag Portrait_Neutral;
    FGameplayTag Portrait_Aggressive;

    FGameplayTag Portrait_Submissive;
    FGameplayTag Portrait_Logical;
    FGameplayTag Portrait_Silent;

	// Location Action Gameplay Tags
    FGameplayTag Action_System_Computer;
    FGameplayTag Action_System_Sleep;
    FGameplayTag Action_System_Save;

    // States
    FGameplayTag State_Fatigued;

    FGameplayTag Attribut_Player_Sanity;

private:
    static FTLG_Data_Gameplay_Tags TLG_Data_Gameplay_Tags;

};
//------------------------------------------------------------------------------------------------------------

