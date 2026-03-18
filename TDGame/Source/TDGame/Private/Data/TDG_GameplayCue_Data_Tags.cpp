//------------------------------------------------------------------------------------------------------------
#include <Data/TDG_GameplayCue_Data_Tags.h>
//------------------------------------------------------------------------------------------------------------




// FTDG_GameplayCue_Data_Tags
FTDG_GameplayCue_Data_Tags FTDG_GameplayCue_Data_Tags::TDG_Data_Gameplay_Tags;
//------------------------------------------------------------------------------------------------------------
const FTDG_GameplayCue_Data_Tags &FTDG_GameplayCue_Data_Tags::Get()
{
    return TDG_Data_Gameplay_Tags;
}
//------------------------------------------------------------------------------------------------------------
void FTDG_GameplayCue_Data_Tags::Initialize_Native_Tags()
{
    UGameplayTagsManager &gameplay_tags_manager = UGameplayTagsManager::Get();

    TDG_Data_Gameplay_Tags.GameplayCue_Tutorial_Sound = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.Tutorial.Sound") );
    TDG_Data_Gameplay_Tags.GameplayCue_Tutorial_Static = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.Tutorial.Static"));
    TDG_Data_Gameplay_Tags.GameplayCue_Tutorial_Niagara = gameplay_tags_manager.AddNativeGameplayTag(TEXT("GameplayCue.Tutorial.Niagara"));
}
//------------------------------------------------------------------------------------------------------------
