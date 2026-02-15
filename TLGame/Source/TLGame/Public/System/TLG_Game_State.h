//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/GameStateBase.h>

#include <TLG_Game_State.generated.h>
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ETLG_Game_State: uint8
{
    None,
    Game,
	Menu_Pause,
    Menu_Main,
	Game_Over
};
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOn_Time_Updated, int32, hours, int32, minutes, int32, minutes_delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Updated_Day, int32, day_count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Game_State_Changed, ETLG_Game_State, tlg_game_state);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Over);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Resumed);
DECLARE_MULTICAST_DELEGATE(FOn_Game_Menu_Paused);
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Game_State : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ATLG_Game_State();

    void Game_Menu_Paused();
    void Game_Resume();
    void Game_Over();
    void Advance_Time(int32 minutes_to_add);
    int32 Get_Current_Day() const;

    mutable FOn_Game_Over On_Game_Over;
    mutable FOn_Game_Resumed On_Game_Resumed;
    mutable FOn_Game_Menu_Paused On_Game_Menu_Paused;

    UPROPERTY(BlueprintAssignable) FOn_Time_Updated On_Updated_Time;
    UPROPERTY(BlueprintAssignable) FOn_Updated_Day On_Updated_Day;
    UPROPERTY(BlueprintAssignable) FOn_Game_State_Changed On_Game_State_Changed;

private:
    ETLG_Game_State TLG_Game_State;

    UPROPERTY(VisibleAnywhere) int32 Current_Time_Minutes;
    UPROPERTY(VisibleAnywhere) int32 Current_Time_Day = 1;
    UPROPERTY(EditDefaultsOnly) int32 Max_Time_Minutes = 1440;

};
//------------------------------------------------------------------------------------------------------------
