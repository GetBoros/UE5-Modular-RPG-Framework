//------------------------------------------------------------------------------------------------------------
#include "GBAI.h"
//------------------------------------------------------------------------------------------------------------
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "Debugger/GBAI_Debugger_Category.h"  // Твой хедер категории
#endif
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "FGBAIModule"
//------------------------------------------------------------------------------------------------------------
void FGBAIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_GAMEPLAY_DEBUGGER
// Получаем модуль дебаггера
    IGameplayDebugger& gameplay_debugger = IGameplayDebugger::Get();

    // Регистрируем категорию:
    // 1. "GBAIFood" - уникальное имя категории
    // 2. Делегат создания инстанса
    // 3. Состояние по умолчанию (включено в игре и симуляции)
    // 4. EGameplayDebuggerCategoryState::EnabledInGameAndSimulate
    // 5. Слот (кнопка на NumPad). Пусть будет 5.
    gameplay_debugger.RegisterCategory(
        "GBAIFood",
        IGameplayDebugger::FOnGetCategory::CreateStatic(&FGBAI_Debugger_Category::MakeInstance),
        EGameplayDebuggerCategoryState::EnabledInGameAndSimulate,
        5
    );

    // Опционально: Сообщаем в лог, что все ок
    UE_LOG(LogTemp, Log, TEXT("GBAI: Gameplay Debugger Category Registered"));
#endif

}
//------------------------------------------------------------------------------------------------------------
void FGBAIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

        // --- CHANGE: Обязательно удаляем категорию при выгрузке ---
#if WITH_GAMEPLAY_DEBUGGER
    if (IGameplayDebugger::IsAvailable())
    {
        IGameplayDebugger::Get().UnregisterCategory("GBAIFood");
    }
#endif
}
//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
IMPLEMENT_MODULE(FGBAIModule, GBAI)
//------------------------------------------------------------------------------------------------------------
