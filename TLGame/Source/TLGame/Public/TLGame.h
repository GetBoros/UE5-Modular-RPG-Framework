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

X	- Tutorial, Intro Dialog: If Sanity < 0 hospital, if Emphaty >= 100 im slave without will
X	- Fatigue logic: Block some answers or else
X	- Demo ending 3 Day

*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region BUGS
/*
V	- After pressing button not decreased sanity
V	- After sleep, not increased fatigue
V	- If Sanity 0 Button Continued don`t need or cannot continue

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

V	- Send Widget Controller to Menu Pause, to update text Game Over and other stuff

*/
#pragma endregion
