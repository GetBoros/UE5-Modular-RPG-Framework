//------------------------------------------------------------------------------------------------------------
#include <Types/GBC_Attribute_Info.h>
//------------------------------------------------------------------------------------------------------------




// FGB_Attribute_Info_Item
FGBC_Attribute_Info_Item UGBC_Attribute_Info::Find_Attribute_Info_By_Tag(const FGameplayTag &tag, bool b_log_not_found) const
{
    for (const FGBC_Attribute_Info_Item &item : Attribute_Information)
    {
        if (item.Attribute_Tag.MatchesTagExact(tag) )
            return item;
    }

    if (b_log_not_found)
        UE_LOG(LogTemp, Error, TEXT("Can't find Info for Tag [%s] in AttributeInfo Asset"), *tag.ToString() );

    return FGBC_Attribute_Info_Item();
}
//------------------------------------------------------------------------------------------------------------