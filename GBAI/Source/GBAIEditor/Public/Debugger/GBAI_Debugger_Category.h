//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayDebuggerCategory.h>
//------------------------------------------------------------------------------------------------------------
class AActor;
class APlayerController;
class FCanvas;
//------------------------------------------------------------------------------------------------------------
class FGBAI_Debugger_Category : public FGameplayDebuggerCategory
{
public:
    FGBAI_Debugger_Category();

    virtual void CollectData(APlayerController *owner_pc, AActor *debug_actor);
    virtual void DrawData(APlayerController *owner_pc, FGameplayDebuggerCanvasContext &canvas_context);

    static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:
    struct FDebugData
    {
        bool Has_Food_Component = false;
        float Current_Hunger = -1.0f;
        FString Actor_Name;
        FString Current_State;

        // --- CHANGE: Add method for serialization FArchive &ar - this "thread" data. Operator << work for both adges (read and write)
        void Serialize(FArchive &ar)
        {
            ar << Actor_Name;
            ar << Current_Hunger;
            ar << Current_State;
            ar << Has_Food_Component;
        }
    };
    FDebugData data;
};
//------------------------------------------------------------------------------------------------------------
