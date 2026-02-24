//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>

#include <Interfaces/TLG_Interaction_Interface.h>
#include <Data/TLG_Types.h>
#include <Data/TLG_Data_Location.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOn_Dialogue_Ended);
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Player_State;
class ATLG_Game_State;
class UTLG_Data_Enemy;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController, public ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();
    virtual void SetupInputComponent();

    virtual void Location_Enter(UTLG_Data_Location *tlg_data_location);
    virtual void Location_Action(const FTLG_Location_Action &tlg_location_action);
    virtual void Request_Menu_Main_Pause(const ETLG_Game_Flow_Option tlg_game_flow_option);

    void Handle_Player_Decision(const FPlayer_Response &player_response);  // Call UI when player press button
    void Set_TLG_Data_Location_Current(UTLG_Data_Location *tlg_data_location);
    void Set_Dialogue_Current(UDataTable *data_table);

    FOn_Dialogue_Ended On_Dialogue_Ended;

private:
    void Spawn_Location_Enemies(TArray<FTLG_Location_Enemy> tlg_location_enemies);

    void Dialogue_Start(const FName &row_id);
    void Dialogue_End();

    void On_Pressed_ESC();

    void Play_Ambient_Sound(USoundBase *sound_base_to_play);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_HUD> TLG_HUD;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Game_State> TLG_Game_State;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Player_State> TLG_Player_State;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Enemy> TLG_Data_Enemy_Current;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Current;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAudioComponent> Audio_Component_Ambient;

    UPROPERTY(EditAnywhere) TObjectPtr<UDataTable> DT_Dialogue_Current;

};
//------------------------------------------------------------------------------------------------------------
