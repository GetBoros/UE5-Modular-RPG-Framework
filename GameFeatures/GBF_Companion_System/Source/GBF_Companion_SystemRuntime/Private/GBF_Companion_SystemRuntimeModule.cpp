//------------------------------------------------------------------------------------------------------------
#include <GBF_Companion_SystemRuntimeModule.h>
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "FGBF_Companion_SystemRuntimeModule"
//------------------------------------------------------------------------------------------------------------




// FGBF_Companion_SystemRuntimeModule
void FGBF_Companion_SystemRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}
//------------------------------------------------------------------------------------------------------------
void FGBF_Companion_SystemRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading, we call this function before unloading the module.
}
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FGBF_Companion_SystemRuntimeModule, GBF_Companion_SystemRuntime)
//------------------------------------------------------------------------------------------------------------
