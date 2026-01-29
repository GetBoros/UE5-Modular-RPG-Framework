//------------------------------------------------------------------------------------------------------------
#include <Components/GBUIC_Text_Block_Typewriter.h>
#include <TimerManager.h>
#include <Engine/World.h>
//------------------------------------------------------------------------------------------------------------




// UGBUIC_Text_Block_Typewriter
void UGBUIC_Text_Block_Typewriter::Start_Typewriter(const FText &text_to_type, float speed)
{
    UWorld *world;

    world = GetWorld();
    if (world == 0)
        return;
    world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);  // Reset

    Full_Text_String = text_to_type.ToString();
    Current_Char_Index = 0;

	SetText(FText::GetEmpty() );  // Visually clear text
    
    world->GetTimerManager().SetTimer(Typewriter_Timer_Handle, this, &UGBUIC_Text_Block_Typewriter::Handle_Typewriter_Tick, speed, true);  // Enable timer to call Handle_Typewriter_Tick every 'speed' seconds
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Text_Block_Typewriter::Skip_Typewriter()
{
    UWorld *world;
    
    world = GetWorld();
    if (world != 0)
        world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);

	SetText(FText::FromString(Full_Text_String) );  // Set full text

    On_Text_Block_Typewriter_Finished.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void UGBUIC_Text_Block_Typewriter::Handle_Typewriter_Tick()
{
    UWorld *world;

    Current_Char_Index++;

	const FString sub_string = Full_Text_String.Left(Current_Char_Index);  // Get left substring
    SetText(FText::FromString(sub_string) );

    if (Current_Char_Index <= Full_Text_String.Len())  // If finished
        return;

    world = GetWorld();
    if (world != 0)
        world->GetTimerManager().ClearTimer(Typewriter_Timer_Handle);

    On_Text_Block_Typewriter_Finished.Broadcast();
}
//------------------------------------------------------------------------------------------------------------