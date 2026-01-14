//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Typewriter_Text.h>

#include <TimerManager.h>
#include <Engine/World.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Typewriter_Text
void UTLG_Typewriter_Text::Start_Typewriter(const FText &text_to_type, float speed)
{
    UWorld* world = GetWorld();
    if (world == 0)
        return;

    // 1. Сброс
    world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);

    Full_Text_String = text_to_type.ToString();
    Current_Char_Index = 0;

    // 2. Очищаем текст визуально
    SetText(FText::GetEmpty() );

    // 3. Запускаем таймер (Loop = true) Он будет вызывать Handle_Typewriter_Tick каждые 'speed' секунд
    world->GetTimerManager().SetTimer(Typewriter_Timer_Handle, this, &UTLG_Typewriter_Text::Handle_Typewriter_Tick, speed, true);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Typewriter_Text::Skip_Typewriter()
{
    UWorld* world = GetWorld();
    if (world != 0)
    {
        world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);
    }

    // Показываем всё сразу
    SetText(FText::FromString(Full_Text_String));

    On_Typewriter_Finished.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Typewriter_Text::Handle_Typewriter_Tick()
{
    Current_Char_Index++;

    // Берем подстроку
    FString sub_string = Full_Text_String.Left(Current_Char_Index);
    SetText(FText::FromString(sub_string));

    // Проверка на конец
    if (Current_Char_Index >= Full_Text_String.Len())
    {
        UWorld* world = GetWorld();
        if (world != 0)
        {
            world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);
        }

        On_Typewriter_Finished.Broadcast();
    }
}
//------------------------------------------------------------------------------------------------------------