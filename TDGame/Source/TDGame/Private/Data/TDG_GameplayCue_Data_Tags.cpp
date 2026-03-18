//------------------------------------------------------------------------------------------------------------
#include <Data/TDG_GameplayCue_Data_Tags.h>
//------------------------------------------------------------------------------------------------------------




// FTDG_GameplayCue_Data_Tags
FTDG_GameplayCue_Data_Tags FTDG_GameplayCue_Data_Tags::TDG_GameplayCue_Data_Tags;
//------------------------------------------------------------------------------------------------------------
const FTDG_GameplayCue_Data_Tags &FTDG_GameplayCue_Data_Tags::Get()
{
    return TDG_GameplayCue_Data_Tags;
}
//------------------------------------------------------------------------------------------------------------
void FTDG_GameplayCue_Data_Tags::Initialize_Native_Tags()
{
    UGameplayTagsManager &gameplay_tags_manager = UGameplayTagsManager::Get();

    TDG_GameplayCue_Data_Tags.GameplayCue_TDG_Tutorial_Sound = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.TDG.Tutorial.Sound") );
    TDG_GameplayCue_Data_Tags.GameplayCue_TDG_Tutorial_Static = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.TDG.Tutorial.Static") );
    TDG_GameplayCue_Data_Tags.GameplayCue_TDG_Tutorial_Niagara = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.TDG.Tutorial.Niagara") );
}
//------------------------------------------------------------------------------------------------------------
