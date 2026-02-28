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
struct FTLG_Location_Enemy;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController, public ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    ATLG_Player_Controller();

    virtual void BeginPlay();
    virtual void SetupInputComponent();

    virtual void Location_Enter(UTLG_Data_Location *tlg_data_location);
    virtual void Location_Action(const FTLG_Location_Action &tlg_location_action);
    virtual void Request_Menu_Main_Pause(const ETLG_Game_Flow_Option tlg_game_flow_option);

    void Temp();
    void Set_TLG_Data_Location_Current(UTLG_Data_Location *tlg_data_location);

private:
    void Spawn_Location_Enemies();

    void On_Pressed_ESC();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_HUD> TLG_HUD;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Game_State> TLG_Game_State;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Player_State> TLG_Player_State;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Current;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TArray<FTLG_Location_Enemy> TLG_Location_Enemies;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Component_Dialogue> TLG_Component_Dialogue;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Component_Navigation> TLG_Component_Navigation;

};
//------------------------------------------------------------------------------------------------------------
