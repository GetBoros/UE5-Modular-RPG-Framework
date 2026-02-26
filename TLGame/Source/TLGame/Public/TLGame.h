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
V	- Part 1:
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
V	- Implement State Tree for enemy dialogue
V	- Add tutorial enemy with simple state tree to show how it work

X	- Part 2:
V	- Show buttons as invalid or don`t show if can`t use them?
V	- Add more than one enemy in location
V	- Move logic from Widget_HUD to cpp, all good to do this
V	- Move Spawn_Text_Floating to UTLG_Widget_Stats_Bar
V	- Change to correct this Get_TLG_Widget_Menu_Pause()->Handle_Widget_Controller();  // !!! TEMP
X	- UTLG_Widget_Stats_Bar change dynamic binding to non dynamic
X	- Add tooltip to buttons action and locations
X	- Refactoring UTLG_Widget_HUD and UTLG_Widget_Stats_Bar
X	- Broadcast_Initial_Values add fatigue
X	- Add Icon to fatigued
X	- 

X	- Part 3:
X	- Need a lot of content for 3 day, and make balance
X	-

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region BUGS_FIXED
/*

V	- Fix: Need empaty to show up when changed
V	- Fix: Tool tip without info about stat
V	- Game time when start don`t show
V	- Fix: Can sleep 4 day to win game

*/
#pragma endregion

//------------------------------------------------------------------------------------------------------------
#pragma region BUGS
/*

X	- Fix: Need empty portrait, now show portrait main hero
X	- 
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region HELP
/*
	- To add Gameplay Tags, use the following pattern:
		- UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PORTRAIT_AGGRESSIVE)  // .h
		- UE_DEFINE_GAMEPLAY_TAG(TAG_PORTRAIT_AGGRESSIVE, TEXT("Visual.Portrait.Aggressive"))  // .cpp

	StateTree:
	- Evaluators:
		- Tick before statetree || Evaluators only need to read data
	- Global Tasks:
		- Tasks work always, if state tree is alive || Watch Sanity params or else || 
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

X	- More than one enemies in room
X	- If player enter to the room he can choose talk or not, if enemies doesn`t talk to him firstly
X	- 
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region REFACTORINGS
/*

X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
