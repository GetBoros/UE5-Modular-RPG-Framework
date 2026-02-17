//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/GameModeBase.h>

#include <TLG_Game_Mode.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Data_Location;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();

private:
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTLG_Data_Location> Player_Start_Location;
};
//------------------------------------------------------------------------------------------------------------
