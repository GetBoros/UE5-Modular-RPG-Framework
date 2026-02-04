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
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}
//------------------------------------------------------------------------------------------------------------
void FTLGameModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FTLGameModule, TLGame)
//------------------------------------------------------------------------------------------------------------
