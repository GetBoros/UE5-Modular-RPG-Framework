//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>

#include <Interfaces/TLG_Interaction_Interface.h>
#include <Data/TLG_Types.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Player_State;
class ATLG_Game_State;
class UTLG_Component_Dialogue;
class UTLG_Component_Navigation;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController, public ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    ATLG_Player_Controller();

    virtual void BeginPlay();
    virtual void SetupInputComponent();

    virtual void Location_Action(const FTLG_Location_Action &tlg_location_action);
    virtual void Request_Menu_Main_Pause(const ETLG_Game_Flow_Option tlg_game_flow_option);

private:
    void Handle_Location_Encounter();

    void On_Pressed_ESC();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_HUD> TLG_HUD;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Game_State> TLG_Game_State;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Player_State> TLG_Player_State;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Component_Dialogue> TLG_Component_Dialogue;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Component_Navigation> TLG_Component_Navigation;

};
//------------------------------------------------------------------------------------------------------------
