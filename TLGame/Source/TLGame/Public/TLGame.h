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
V	- Part 1: Completed
X	- Part 2: In progress
X	- Add tooltip to buttons action and locations
X		- If player can`t use button, need show tooltip with reason or else, if can use show tooltip with info about action
X	- 

X	- Part 3: In progress
X	- Need a lot of content for 3 day, and make balance
X	-

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region BUGS_FIXED
/*

X	- 

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
X	- NPC must live, move and do something, not just wait for player to talk to them, they can talk to player if he in the room, or else
X	- Inventory system, player can find some items in the location and use them in the future, or else
X	- Localization Ru, Eng, Ua other.
X	- Patchings
X	- Tool tip on player Image to show stats? Or enemy
X		- Second Attributes like STR, INT, WIS and other
X	- 

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region REFACTORINGS
/*

V	- ATLG_Player_Controller add actor components for Audio, dialogue, enemy, location and else, to not use pointers to actors and data in controller

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
