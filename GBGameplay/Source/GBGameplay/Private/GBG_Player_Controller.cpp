//------------------------------------------------------------------------------------------------------------
#include <GBG_Player_Controller.h>

#include <EnhancedInputSubsystems.h>
//------------------------------------------------------------------------------------------------------------



// AGB_PlayerController
void AGBG_Player_Controller::OnPossess(APawn *pawn)
{
	Super::OnPossess(pawn);

	if (UEnhancedInputLocalPlayerSubsystem *subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer() ) )
	{
		subsystem->ClearAllMappings();

		if (Default_Mapping_Context != 0)
			subsystem->AddMappingContext(Default_Mapping_Context, 0);
	}
}
//------------------------------------------------------------------------------------------------------------
