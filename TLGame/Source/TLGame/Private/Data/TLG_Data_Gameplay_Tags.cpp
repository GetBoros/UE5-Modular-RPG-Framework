//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Data_Gameplay_Tags.h>
//------------------------------------------------------------------------------------------------------------



// FTLG_Data_Gameplay_Tags
FTLG_Data_Gameplay_Tags FTLG_Data_Gameplay_Tags::Gameplay_Tags;
//------------------------------------------------------------------------------------------------------------
const FTLG_Data_Gameplay_Tags& FTLG_Data_Gameplay_Tags::Get()
{
    return Gameplay_Tags;
}
//------------------------------------------------------------------------------------------------------------
void FTLG_Data_Gameplay_Tags::Initialize_Native_Tags()
{
    // Gameplay_Tags.Portrait_Aggressive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Portrait.Aggressive"), FString("Portrait for aggressive mood") );
    // Gameplay_Tags.Portrait_Neutral = UGameplayTagsManager::Get().AddNativeGameplayTag( FName("Portrait.Neutral"), FString("Default portrait") );
    Gameplay_Tags.Portrait_Happy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Happy"), FString("Portrait for happy mood") );
    Gameplay_Tags.Action_System_Sleep = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.System.Sleep"), FString("Trigger for end of day logic") );
}
//------------------------------------------------------------------------------------------------------------
