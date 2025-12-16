//------------------------------------------------------------------------------------------------------------
#include <Debugger/GBAI_Debugger_Category.h>
//------------------------------------------------------------------------------------------------------------
#if WITH_GAMEPLAY_DEBUGGER  // !!! TEMP
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/Actor.h>
#include <AI/GBAI_Character.h>
//------------------------------------------------------------------------------------------------------------
FGBAI_Debugger_Category::FGBAI_Debugger_Category()
{
    SetDataPackReplication<FDebugData>(&data);  // set default update
}
//------------------------------------------------------------------------------------------------------------
TSharedRef<FGameplayDebuggerCategory> FGBAI_Debugger_Category::MakeInstance()
{
	return MakeShareable(new FGBAI_Debugger_Category());
}
//------------------------------------------------------------------------------------------------------------
void FGBAI_Debugger_Category::CollectData(APlayerController* owner_pc, AActor* debug_actor)
{
    if (debug_actor == 0)
        return;

    data.Actor_Name = debug_actor->GetName();

    if (AGBAI_Character *my_char = Cast<AGBAI_Character>(debug_actor) )  // if seccuss receive data
    {
        data.Current_Hunger = my_char->Get_Hunger(); // Убедись, что переменная public или есть Get()

        if (data.Current_Hunger < 20.0f)  // Simple logic for status
            data.Current_State = TEXT("STARVING");
        else
            data.Current_State = TEXT("Satisfied");
    }
    else  // if not watch at character
    {
        data.Current_Hunger = -1.0f;
        data.Current_State = TEXT("Not a GBAI Character");
    }
}
//------------------------------------------------------------------------------------------------------------
void FGBAI_Debugger_Category::DrawData(APlayerController* owner_pc, FGameplayDebuggerCanvasContext& canvas_context)
{
    if (data.Actor_Name.IsEmpty() == true)
    {
        canvas_context.Print(TEXT("{red}No Actor Selected") );

        return;
    }

    canvas_context.Printf(TEXT("{green}Target: {white}%s"), *data.Actor_Name);  // Draw name

    if (data.Current_Hunger >= 0.0f)  // Draw hunger with color (Rad if small, green if a lot)
    {
        const FString color = (data.Current_Hunger < 30.0f) ? TEXT("{red}") : TEXT("{green}");
        
        canvas_context.Printf(TEXT("Hunger: %s%.1f / 100.0"), *color, data.Current_Hunger);
        canvas_context.Printf(TEXT("State: {yellow}%s"), *data.Current_State);
    }
    else
    {
        canvas_context.Print(TEXT("{grey}No AI data available for this actor"));
    }

    // 3. Draw at up of head
    if (data.Current_Hunger >= 0.0f)
    {
        // Find position upper head
        // We can use ProjectProjectedPoint if transfered position here
        // But GameplayDebugger can draw at world from FGameplayDebuggerCanvasContext
        // Simplified variant: just draw a green circlet if not our bot
        // canvas_context.DrawPoint(FVector(0,0,0), FColor::Green); <--- Need world coords

        // Imporntant: If need draw upper head in DrawData, we need to transfer a position actor in struct FDebugData.
    }
}
//------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------