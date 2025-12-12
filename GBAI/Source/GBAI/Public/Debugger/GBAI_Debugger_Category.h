//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#if WITH_GAMEPLAY_DEBUGGER
//------------------------------------------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"
//------------------------------------------------------------------------------------------------------------
class AActor;
class APlayerController;
class FCanvas;
//------------------------------------------------------------------------------------------------------------
class FGBAI_Debugger_Category : public FGameplayDebuggerCategory
{
public:
    FGBAI_Debugger_Category();

    virtual void CollectData(APlayerController* owner_pc, AActor* debug_actor) override;
    virtual void DrawData(APlayerController* owner_pc, FGameplayDebuggerCanvasContext& canvas_context) override;

    static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:
    struct FDebugData
    {
        FString actor_name;
        float current_hunger = -1.0f;
        FString current_state;
        bool has_food_component = false;

        // --- CHANGE: Добавляем метод сериализации ---
        // FArchive &ar - это "поток" данных. Оператор << работает в обе стороны (запись и чтение).
        void Serialize(FArchive& ar)
        {
            ar << actor_name;
            ar << current_hunger;
            ar << current_state;
            ar << has_food_component;
        }
        // --------------------------------------------
    };

    FDebugData data;
};
//------------------------------------------------------------------------------------------------------------
#endif // WITH_GAMEPLAY_DEBUGGER
//------------------------------------------------------------------------------------------------------------