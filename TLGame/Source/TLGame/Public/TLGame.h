//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
class FTLGameModule : public IModuleInterface
{
public:
	virtual void StartupModule();
	virtual void ShutdownModule();

};
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
#pragma region TASKS
/*
V	- In Controller work with Enemy, not just DT or other data
V	- Tooltips
V		- Need visual simple
V	- Press ESC to open Exit from game or Restart
V		- Menu with 3 options: Exit, Restart, Continue
V		- If lose game need show text Game Over
V	- UI Sound press buttons or something else
V	- Demo ending 3 Day
V	- Tutorial, Intro Dialog: If Sanity < 0 hospital, if Emphaty >= 100 im slave without will
V	- Can sleep only if fatigue more then 50+?
V	- Fatigue logic: Block some answers or else

	Part 2:
X	- Add tooltip to buttons action and locations
X	- Show buttons as invalid or don`t show if can`t use them?
X	- Implement State Tree for enemy dialogue
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region BUGS
/*

V	- Fix: Tool tip without info about stat
V	- Game time when start don`t show
V	- Fix: Can sleep 4 day to win game
X	- Fix: Need empty portrait, now show portrait main hero

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region HELP
/*
	- To add Gameplay Tags, use the following pattern:
		- UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PORTRAIT_AGGRESSIVE)  // .h
		- UE_DEFINE_GAMEPLAY_TAG(TAG_PORTRAIT_AGGRESSIVE, TEXT("Visual.Portrait.Aggressive"))  // .cpp

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region UPDATES
/*

X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region FEATURES
/*

X	- If player have fatigue 50+, location can show option sleep
X	- More than one enemies in room
X	- If player enter to the room he can choose talk or not, if enemies doesn`t talk to him firstly
X	- 
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region REFACTORINGS
/*

V	- Need ATLG_Player_Controller refactoring
V	- UTLG_Widget_HUD must have params TArray<FTLG_Location_Action> for current location and current navigation, and in controller just send it?
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
