//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Data_Enemy.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Data_Enemy 
UTexture2D *UTLG_Data_Enemy::Get_Portrait_By_Tag(const FGameplayTag &tag) const
{
    if (Portraits.Contains(tag) )
        return Portraits[tag];

    return 0;
}
//------------------------------------------------------------------------------------------------------------
UDataTable *UTLG_Data_Enemy::Get_Dialogue_Table_By_Tag(const FGameplayTag &tag) const
{
    if (Dialogue_Tables.Contains(tag) )
        return Dialogue_Tables[tag];

    return 0;
}
//------------------------------------------------------------------------------------------------------------
