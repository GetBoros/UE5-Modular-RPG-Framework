//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/ActorComponent.h>

#include <TLG_Component_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOn_Dialogue_Ended);
//------------------------------------------------------------------------------------------------------------
struct FPlayer_Response;
class UTLG_Data_Enemy;
class ATLG_HUD;
class ATLG_Player_State;
//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class TLGAME_API UTLG_Component_Dialogue : public UActorComponent
{
	GENERATED_BODY()

public:
	UTLG_Component_Dialogue();

	virtual void BeginPlay();
	
	void Init(ATLG_HUD *tlg_hud, ATLG_Player_State *tlg_player_state);

	void Dialogue_Start(const FName &row_id, UTLG_Data_Enemy *tlg_data_enemy);
	void Dialogue_End();
	void Handle_Player_Decision(const FPlayer_Response &player_response);
    void Set_Dialogue_Current(UDataTable *data_table);

	FOn_Dialogue_Ended On_Dialogue_Ended;

private:
	UPROPERTY(EditAnywhere) TObjectPtr<UDataTable> DT_Dialogue_Current;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_HUD> TLG_HUD;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Player_State> TLG_Player_State;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Enemy> TLG_Data_Enemy_Current;  // !!! TEMP wrong place for enemy data, need refactoring

};
//------------------------------------------------------------------------------------------------------------
