//------------------------------------------------------------------------------------------------------------
#include <TLGame.h>
#include <Data/TLG_Data_Gameplay_Tags.h>
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "FTLGameModule"
//------------------------------------------------------------------------------------------------------------




// FTLGameModule
void FTLGameModule::StartupModule()
{
	FTLG_Data_Gameplay_Tags::Initialize_Native_Tags();
}
//------------------------------------------------------------------------------------------------------------
void FTLGameModule::ShutdownModule()
{
	
}
//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FTLGameModule, TLGame)
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
#pragma region TASKS_DONE
/*
V	- Part 1: Completed
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
V	- UTLG_Widget_Stats_Bar change dynamic binding to non dynamic
V	- Refactoring UTLG_Widget_HUD and UTLG_Widget_Stats_Bar
V	- Broadcast_Initial_Values add fatigue
V	- Add Icon to fatigued
V	- Add tooltip to buttons action and locations

X	- Part 3: In progress
V	- Add Android support, and make it work, or else
V	- Have problem with Dialogue, and race condition
V	- Localization Ru, Eng, Ua other.
V	- Fix bug spawn enemie when switch location with out enemie
V	- Add condition to spawn if don`t have tags
V	- Patchings


*/
#pragma endregion
//------------------------------------------------------------------------------------------------------------
