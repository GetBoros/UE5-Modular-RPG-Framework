//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <NativeGameplayTags.h>
//------------------------------------------------------------------------------------------------------------
struct FTLG_Data_Gameplay_Tags
{
public:
    static const FTLG_Data_Gameplay_Tags &Get();

    static void Initialize_Native_Tags();

    // Portrait Tags
     FGameplayTag Portrait_Happy;

    // FGameplayTag Portrait_Aggressive;
    // FGameplayTag Portrait_Neutral;
    // FGameplayTag Portrait_Submissive;
    // FGameplayTag Portrait_Logical;
    // FGameplayTag Portrait_Silent;

    // Action Tags (для нашей новой системы действий)
    FGameplayTag Action_System_Sleep;
    FGameplayTag Action_System_Save;

private:
    static FTLG_Data_Gameplay_Tags Gameplay_Tags;
};
//------------------------------------------------------------------------------------------------------------

