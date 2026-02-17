//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/GameModeBase.h>

#include <TLG_Game_Mode.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Data_Location;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();

private:
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTLG_Data_Location> Player_Start_Location;

};
//------------------------------------------------------------------------------------------------------------
#pragma region TASKS
/*
// Initializations
X   - Spawn player
X   - Save Load
X   - Game Dificulty

// Gameplay
X   - Block Controlls or enable controlls
X   - Show display end of the day
X   - Win/lose conditions
X   - Calculate  consiquences of player decision (if Sanity < 20, girl go out)
X   -

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
