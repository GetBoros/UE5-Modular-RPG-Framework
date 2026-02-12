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
X		- Need visual
X	- Press ESC to open Exit from game or Restart
X	- Fatigue logic: Block some answers or else
X	- UI Sound press buttons or something else
X	- Tutorial, Intro Dialog: If Sanity < 0 hospital, if Emphaty >= 100 im slave without will
X	- Demo ending 3 Day, 10 minits


*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
#pragma region BUGS
/*
V	- After pressing button not decreased sanity
V	- After sleep, not increased fatigue
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
