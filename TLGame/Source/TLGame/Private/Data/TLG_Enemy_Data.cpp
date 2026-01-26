//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Enemy_Data.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Enemy_Data
UTexture2D *UTLG_Enemy_Data::Get_Portrait_By_Tag(const FGameplayTag &tag) const
{
    if (Portraits.Contains(tag) )
        return Portraits[tag];

    return 0;
}
//------------------------------------------------------------------------------------------------------------
UDataTable *UTLG_Enemy_Data::Get_Dialogue_Table_By_Tag(const FGameplayTag &tag) const
{
    if (Dialogue_Tables.Contains(tag) )
        return Dialogue_Tables[tag];

    return 0;
}
//------------------------------------------------------------------------------------------------------------
