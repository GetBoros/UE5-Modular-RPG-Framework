//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <NativeGameplayTags.h>
//------------------------------------------------------------------------------------------------------------
struct FTDG_GameplayCue_Data_Tags
{
public:
    static void Initialize_Native_Tags();
    
    static const FTDG_GameplayCue_Data_Tags &Get();

    FGameplayTag GameplayCue_TDG_Tutorial_Sound;
    FGameplayTag GameplayCue_TDG_Tutorial_Static;
    FGameplayTag GameplayCue_TDG_Tutorial_Niagara;

private:
    static FTDG_GameplayCue_Data_Tags TDG_GameplayCue_Data_Tags;

};
//------------------------------------------------------------------------------------------------------------

