//------------------------------------------------------------------------------------------------------------
#include <Subsystems/TLG_Subsystem_Story.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Subsystem_Story
bool UTLG_Subsystem_Story::Add_Story_Flag(FGameplayTag flag)
{
	if (flag.IsValid() )
	{
		Story_Flags.AddTag(flag);

		return true;
	}

	return false;
}
//------------------------------------------------------------------------------------------------------------
bool UTLG_Subsystem_Story::Has_Story_Flag(FGameplayTag flag)
{
	if (flag.MatchesAny(Story_Flags) )
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------------------------------------
