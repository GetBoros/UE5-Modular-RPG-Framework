//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/GameStateBase.h>

#include <TLG_Game_State.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOn_Time_Updated, int32, hours, int32, minutes, int32, minutes_delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Updated_Day, int32, day_count);
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Game_State : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ATLG_Game_State();

    void Advance_Time(int32 minutes_to_add);

    int32 Get_Current_Day() const;

    UPROPERTY(BlueprintAssignable) FOn_Time_Updated On_Updated_Time;
    UPROPERTY(BlueprintAssignable) FOn_Updated_Day On_Updated_Day;
private:
    UPROPERTY(VisibleAnywhere) int32 Current_Time_Minutes;
    UPROPERTY(VisibleAnywhere) int32 Current_Time_Day = 1;
    UPROPERTY(EditDefaultsOnly) int32 Max_Time_Minutes = 1440;

};
//------------------------------------------------------------------------------------------------------------
