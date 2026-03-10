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
V	- Part 2: Completed

X	- Part 3: In progress
X	- Make Action button to use GA by tags
X	- Tool tip on player Image to show stats? Or enemy
X		- Second Attributes like STR, INT, WIS and other
V	- If player can`t use button, need show tooltip with reason or else, if can use show tooltip with info about action
X		- Example. Some take shower. Toilet is not empty. And other.
X	- Need a lot of content for 3 day, and make balance
X	- Make ST_ for stats and other static FTexts for better localization and balance in future, and use them in code, not hardcode
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

	TLG_Localization:
		- Disable livecode in editor preferences

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
