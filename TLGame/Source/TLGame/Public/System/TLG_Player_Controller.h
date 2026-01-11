//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>
#include <Data/TLG_Types.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Dialogue;
class ATLG_Player_State;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();

    UFUNCTION(BlueprintCallable) void Process_Player_Decision(const FPlayer_Response &choice);  // Call UI when player press button

    ATLG_Player_State *Get_TLG_Player_State() const;
    void Apply_Response_Cost(float cost);
    void Apply_Response_Effects(const FGameplayTagContainer &tags);

};
//------------------------------------------------------------------------------------------------------------
