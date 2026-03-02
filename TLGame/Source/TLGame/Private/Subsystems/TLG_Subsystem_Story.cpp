//------------------------------------------------------------------------------------------------------------
#include <Subsystems/TLG_Subsystem_Story.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Subsystem_Story
bool UTLG_Subsystem_Story::Add_Story_Flag(FGameplayTag flag)
{
	if (flag.IsValid() != true)
		return false;

	Story_Flags.AddTag(flag);
	
	return true;
}
//------------------------------------------------------------------------------------------------------------
bool UTLG_Subsystem_Story::Has_Story_Flag(FGameplayTag flag)
{
	if (flag.MatchesAny(Story_Flags) == true )
		return true;

	return false;
}
//------------------------------------------------------------------------------------------------------------
FGameplayTagContainer UTLG_Subsystem_Story::Get_Story_Flags() const
{
	return Story_Flags;
}
//------------------------------------------------------------------------------------------------------------
