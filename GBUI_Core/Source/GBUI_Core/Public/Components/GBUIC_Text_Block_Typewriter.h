//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/TextBlock.h>

#include <GBUIC_Text_Block_Typewriter.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Text_Block_Typewriter_Finished);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_CORE_API UGBUIC_Text_Block_Typewriter : public UTextBlock
{
	GENERATED_BODY()

public:
    void Start_Typewriter(const FText &text_to_type, float speed = 0.05f);
    void Skip_Typewriter();

    UPROPERTY(BlueprintAssignable) FOn_Text_Block_Typewriter_Finished On_Text_Block_Typewriter_Finished;

private:
    int32 Current_Char_Index = 0;

    FString Full_Text_String;
    FTimerHandle Typewriter_Timer_Handle;
    
    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Typewriter_Tick();  // Func for delegate

};
//------------------------------------------------------------------------------------------------------------
