//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Data_Enemy.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Data_Enemy 
UTexture2D *UTLG_Data_Enemy::Get_Portrait_For_Mood(const FGameplayTag &gameplay_tag_mood) const
{
    if (Portraits_By_Scenario.Contains(gameplay_tag_mood) )
        return Portraits_By_Scenario[gameplay_tag_mood];

    return 0;
}
//------------------------------------------------------------------------------------------------------------
