//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Data_Gameplay_Tags.h>
//------------------------------------------------------------------------------------------------------------




// FTLG_Data_Gameplay_Tags
FTLG_Data_Gameplay_Tags FTLG_Data_Gameplay_Tags::TLG_Data_Gameplay_Tags;
//------------------------------------------------------------------------------------------------------------
const FTLG_Data_Gameplay_Tags &FTLG_Data_Gameplay_Tags::Get()
{
    return TLG_Data_Gameplay_Tags;
}
//------------------------------------------------------------------------------------------------------------
void FTLG_Data_Gameplay_Tags::Initialize_Native_Tags()
{
    TLG_Data_Gameplay_Tags.Portrait_Happy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Happy"), FString("Portrait for aggressive mood"));
    TLG_Data_Gameplay_Tags.Portrait_Neutral = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Neutral"), FString("Default portrait"));
    TLG_Data_Gameplay_Tags.Portrait_Aggressive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Angry"), FString("Portrait for aggressive mood"));
    
    TLG_Data_Gameplay_Tags.Portrait_Submissive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Submissive"), FString("Default portrait"));
    TLG_Data_Gameplay_Tags.Portrait_Logical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Logical"), FString("Portrait for happy mood"));
    TLG_Data_Gameplay_Tags.Portrait_Silent= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Visual.Portrait.Silent"), FString("Portrait for happy mood") );

    TLG_Data_Gameplay_Tags.Action_System_Save = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.System.Save"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Action_System_Sleep = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.System.Sleep"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Action_System_Computer = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Action.System.Computer"), FString("Trigger for end of day logic") );

    TLG_Data_Gameplay_Tags.State_Fatigued = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("State.Fatigued"), FString("Trigger for end of day logic") );

    TLG_Data_Gameplay_Tags.Attribut_Player_Sanity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Player.Sanity"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Attribut_Player_Empathy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Player.Empathy"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Attribut_Player_Dominance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Player.Dominance"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Attribut_Player_Fatigued = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Player.Fatigued"), FString("Trigger for end of day logic") );
    
    TLG_Data_Gameplay_Tags.Dialogue_Marina_Intro = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Dialogue.Tutorial.Intro"), FString("Trigger for end of day logic") );
    TLG_Data_Gameplay_Tags.Dialogue_Marina_Intro = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Dialogue.Marina.Intro"), FString("Trigger for end of day logic") );

}
//------------------------------------------------------------------------------------------------------------
