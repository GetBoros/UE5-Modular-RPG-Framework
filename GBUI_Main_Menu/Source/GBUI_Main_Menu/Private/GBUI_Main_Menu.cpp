//------------------------------------------------------------------------------------------------------------
#include "GBUI_Main_Menu.h"
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "FGBUI_Main_MenuModule"
//------------------------------------------------------------------------------------------------------------




// FGBUI_Main_MenuModule
void FGBUI_Main_MenuModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}
//------------------------------------------------------------------------------------------------------------
void FGBUI_Main_MenuModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FGBUI_Main_MenuModule, GBUI_Main_Menu)
//------------------------------------------------------------------------------------------------------------
