//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>

#include <Interfaces/TLG_Interaction_Interface.h>
#include <Data/TLG_Types.h>
#include <Data/TLG_Data_Location.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Player_State;
class UTLG_Data_Enemy;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController, public ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();
    virtual void Execute_Move_To_Location(UTLG_Data_Location *tlg_data_location);
    virtual void Execute_Action(FGameplayTag gameplay_tag_action, int32 time_cost);

    void Handle_Player_Decision(const FPlayer_Response &player_response);  // Call UI when player press button

private:
    void Dialogue_Start(const FName &row_id);
    void Dialogue_End();

    void Apply_Response_Effects(const FGameplayTagContainer &gameplay_tag_container);
    void Play_Ambient_Sound(USoundBase *sound_base_to_play);

    UPROPERTY(meta = (AllowPrivateAccess = "true") ) ATLG_HUD *TLG_HUD;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) ATLG_Player_State *TLG_Player_State;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) UAbilitySystemComponent *Ability_System_Component;
    
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UDataTable> Dialogue_Data_Table;  // !!! TEMP Need take from enemy

    UPROPERTY(EditDefaultsOnly) TObjectPtr<UTLG_Data_Enemy> TLG_Data_Enemy_Current;
    UPROPERTY(EditDefaultsOnly) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Start;

    UPROPERTY(VisibleAnywhere) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Current;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UAudioComponent> Audio_Component_Ambient;

};
//------------------------------------------------------------------------------------------------------------
