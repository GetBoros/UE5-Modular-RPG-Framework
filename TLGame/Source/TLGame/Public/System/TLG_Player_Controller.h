//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>
#include <Data/TLG_Types.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_Player_State;
class ATLG_HUD;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();

    UFUNCTION(BlueprintCallable) void Process_Player_Decision(const FPlayer_Response &choice);  // Call UI when player press button
    
private:
    void Apply_Response_Cost(float cost);
    void Apply_Response_Effects(const FGameplayTagContainer &tags);

    UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true") ) void Dialogue_Start(const FDialogue_Node &node);

    ATLG_HUD *Get_TLG_HUD() const;
    ATLG_Player_State *Get_TLG_Player_State() const;

};
//------------------------------------------------------------------------------------------------------------
