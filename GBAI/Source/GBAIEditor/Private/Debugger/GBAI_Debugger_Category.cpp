//------------------------------------------------------------------------------------------------------------
#include "Debugger/GBAI_Debugger_Category.h"
//------------------------------------------------------------------------------------------------------------
#if WITH_GAMEPLAY_DEBUGGER
//------------------------------------------------------------------------------------------------------------
#include "GameFramework/Actor.h"
#include "CanvasItem.h"
#include "AI/GBAI_Character.h"
//------------------------------------------------------------------------------------------------------------
FGBAI_Debugger_Category::FGBAI_Debugger_Category()
{
    // Настройка частоты обновления (по дефолту)
    SetDataPackReplication<FDebugData>(&data);
}
//------------------------------------------------------------------------------------------------------------
TSharedRef<FGameplayDebuggerCategory> FGBAI_Debugger_Category::MakeInstance()
{
	return MakeShareable(new FGBAI_Debugger_Category());
}
//------------------------------------------------------------------------------------------------------------
void FGBAI_Debugger_Category::CollectData(APlayerController* owner_pc, AActor* debug_actor)
{
    // 1. СБОР ДАННЫХ
    if (debug_actor == 0)
    {
        return;
    }

    data.actor_name = debug_actor->GetName();

    // CHANGE: Пытаемся превратить (Cast) актора в нашего AI персонажа
    if (AGBAI_Character* my_char = Cast<AGBAI_Character>(debug_actor))
    {
        // Если успешно - забираем данные
        data.current_hunger = my_char->Get_Hunger(); // Убедись, что переменная public или есть Get()

        // Простая логика для статуса
        if (data.current_hunger < 20.0f)
        {
            data.current_state = TEXT("STARVING");
        }
        else
        {
            data.current_state = TEXT("Satisfied");
        }
    }
    else
    {
        // Если мы смотрим не на персонажа, а, например, на стену или еду
        data.current_hunger = -1.0f;
        data.current_state = TEXT("Not a GBAI Character");
    }
}
//------------------------------------------------------------------------------------------------------------
void FGBAI_Debugger_Category::DrawData(APlayerController* owner_pc, FGameplayDebuggerCanvasContext& canvas_context)
{
    // 2. ОТРИСОВКА
    if (data.actor_name.IsEmpty() == true)
    {
        canvas_context.Print(TEXT("{red}No Actor Selected"));
        return;
    }

    // Рисуем имя
    canvas_context.Printf(TEXT("{green}Target: {white}%s"), *data.actor_name);

    // Рисуем голод с цветом (Красный если мало, Зеленый если много)
    if (data.current_hunger >= 0.0f)
    {
        FString color = (data.current_hunger < 30.0f) ? TEXT("{red}") : TEXT("{green}");
        canvas_context.Printf(TEXT("Hunger: %s%.1f / 100.0"), *color, data.current_hunger);

        canvas_context.Printf(TEXT("State: {yellow}%s"), *data.current_state);
    }
    else
    {
        canvas_context.Print(TEXT("{grey}No AI data available for this actor"));
    }

    // 3. ОТРИСОВКА НАД ГОЛОВОЙ (Overhead)
    if (data.current_hunger >= 0.0f)
    {
        // Находим позицию над головой актора
        // Примечание: Мы не имеем доступа к самому актору здесь (он может быть на сервере), 
        // но мы можем использовать ProjectProjectedPoint если бы передали позицию.
        // Но GameplayDebugger позволяет рисовать в мире через FGameplayDebuggerCanvasContext.

        // Упрощенный вариант: просто рисуем зеленый кружок, если это наш бот
        // canvas_context.DrawPoint(FVector(0,0,0), FColor::Green); <--- Требует координат мира

        // ВАЖНО: Чтобы рисовать над головой в DrawData, нам нужно было передать позицию актора в struct FDebugData.
        // Давай пока ограничимся текстом слева, так как это стандарт дебаггера.
        // Если очень нужно над головой - скажи, добавим FVector ActorLocation в структуру данных.
    }
}
//------------------------------------------------------------------------------------------------------------
#endif // WITH_GAMEPLAY_DEBUGGER
//------------------------------------------------------------------------------------------------------------