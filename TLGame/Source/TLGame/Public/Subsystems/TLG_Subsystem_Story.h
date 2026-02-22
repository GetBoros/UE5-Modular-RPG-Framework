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
	UFUNCTION(BlueprintCallable) bool Add_Story_Flag(FGameplayTag flag);
	UFUNCTION(BlueprintCallable) bool Has_Story_Flag(FGameplayTag flag);
	
	FGameplayTagContainer Story_Flags;
};
//------------------------------------------------------------------------------------------------------------
