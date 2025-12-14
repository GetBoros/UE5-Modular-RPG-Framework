//------------------------------------------------------------------------------------------------------------
#include <GBAIEditor.h>
#include <GameplayDebugger.h>
#include <Debugger/GBAI_Debugger_Category.h>
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "FGBAIEditorModule"
//------------------------------------------------------------------------------------------------------------
void FGBAIEditorModule::StartupModule()
{
    IGameplayDebugger &gameplay_debugger = FModuleManager::LoadModuleChecked<IGameplayDebugger>("GameplayDebugger");  // load module checked

    //IGameplayDebugger &gameplay_debugger = IGameplayDebugger::Get();  // Get debug module
    // Register Category:
    // 1. "GBAIFood" - uniqe name for catergory
    // 2. delegate for creating instance
    // 3. Default state (included in game)
    // 4. EGameplayDebuggerCategoryState::EnabledInGameAndSimulate
    // 5. Slot button on NumPad 7
    gameplay_debugger.RegisterCategory("GBAIFood", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGBAI_Debugger_Category::MakeInstance), EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 7);
    gameplay_debugger.NotifyCategoriesChanged();

    UE_LOG(LogTemp, Warning, TEXT("GBAIEditor Module Started!"));
}
//------------------------------------------------------------------------------------------------------------
void FGBAIEditorModule::ShutdownModule()
{
    if (IGameplayDebugger::IsAvailable() )
    {
        IGameplayDebugger::Get().UnregisterCategory("GBAIFood");
        IGameplayDebugger::Get().NotifyCategoriesChanged();
    }
}
//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FGBAIEditorModule, GBAIEditor)
//------------------------------------------------------------------------------------------------------------
