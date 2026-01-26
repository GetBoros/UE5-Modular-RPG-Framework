//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>
#include <Data/TLG_Types.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Player_State;
class UTLG_Enemy_Data;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();

    void Handle_Player_Decision(const FPlayer_Response &choice);  // Call UI when player press button

private:
    void Dialogue_Start(const FName &row_id);
    void Dialogue_End();

    void Apply_Response_Effects(const FGameplayTagContainer &tags);

    UPROPERTY(meta = (AllowPrivateAccess = "true") ) ATLG_HUD *TLG_HUD;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) ATLG_Player_State *TLG_Player_State;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) UAbilitySystemComponent *Ability_System_Component;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UDataTable> Dialogue_Data_Table;  // !!! TEMP Need take from enemy

    UPROPERTY(EditDefaultsOnly) TObjectPtr<UTLG_Enemy_Data> Current_Enemy_Data;
};
//------------------------------------------------------------------------------------------------------------
