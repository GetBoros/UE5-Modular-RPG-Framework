//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/GameStateBase.h>

#include <TLG_Game_State.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOn_Time_Updated, int32, hours, int32, minutes, int32, minutes_delta);
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Game_State : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ATLG_Game_State();

    void Advance_Time(int32 minutes_to_add);

    UPROPERTY(BlueprintAssignable) FOn_Time_Updated On_Time_Updated;

private:
    UFUNCTION(BlueprintPure) void Get_Current_Time(int32 &hours, int32 &minutes) const;
    
    UPROPERTY(VisibleAnywhere) int32 Current_Time_Minutes;
    UPROPERTY(EditDefaultsOnly) int32 Max_Time_Minutes = 1440;
};
//------------------------------------------------------------------------------------------------------------
