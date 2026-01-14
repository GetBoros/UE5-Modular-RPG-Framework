//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/TextBlock.h>

#include <TLG_Typewriter_Text.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Typewriter_Finished);
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Typewriter_Text : public UTextBlock
{
    GENERATED_BODY()

public:
    void Start_Typewriter(const FText &text_to_type, float speed = 0.05f);
    void Skip_Typewriter();
    
    UFUNCTION() void Handle_Typewriter_Tick();  // Функция, которую будет дергать таймер

    UPROPERTY(BlueprintAssignable) FOn_Typewriter_Finished On_Typewriter_Finished;


private:
    int32 Current_Char_Index = 0;
    FString Full_Text_String;

    FTimerHandle Typewriter_Timer_Handle;
};
//------------------------------------------------------------------------------------------------------------