//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Typewriter_Text.h>

#include <TimerManager.h>
#include <Engine/World.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Typewriter_Text
void UTLG_Typewriter_Text::Start_Typewriter(const FText &text_to_type, float speed)
{
    UWorld *world = GetWorld();
    if (world == 0)
        return;

    world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);  // Reset

    Full_Text_String = text_to_type.ToString();
    Current_Char_Index = 0;

	SetText(FText::GetEmpty() );  // Visually clear text

	// Enable timer to call Handle_Typewriter_Tick every 'speed' seconds
    world->GetTimerManager().SetTimer(Typewriter_Timer_Handle, this, &UTLG_Typewriter_Text::Handle_Typewriter_Tick, speed, true);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Typewriter_Text::Skip_Typewriter()
{
    UWorld *world = GetWorld();
    if (world != 0)
        world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);

	SetText(FText::FromString(Full_Text_String) );  // Set full text

    On_Typewriter_Finished.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Typewriter_Text::Handle_Typewriter_Tick()
{
    UWorld *world;

    Current_Char_Index++;

	FString sub_string = Full_Text_String.Left(Current_Char_Index);  // Get left substring
    SetText(FText::FromString(sub_string));

	if (Current_Char_Index >= Full_Text_String.Len() )  // If finished
    {
        world = GetWorld();
        if (world != 0)
            world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);

        On_Typewriter_Finished.Broadcast();
    }
}
//------------------------------------------------------------------------------------------------------------