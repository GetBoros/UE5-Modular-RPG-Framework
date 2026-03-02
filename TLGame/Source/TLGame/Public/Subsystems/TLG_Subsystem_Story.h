//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Subsystems/GBC_Gameplay_Message_Subsystem.h>

#include <TLG_Subsystem_Story.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Subsystem_Story : public UGBC_Gameplay_Message_Subsystem
{
    GENERATED_BODY()

public:
	bool Add_Story_Flag(FGameplayTag flag);
	bool Has_Story_Flag(FGameplayTag flag);
	
	FGameplayTagContainer Get_Story_Flags() const;

private:
	FGameplayTagContainer Story_Flags;
};
//------------------------------------------------------------------------------------------------------------
