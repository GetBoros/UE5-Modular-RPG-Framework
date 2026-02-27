//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/ActorComponent.h>

#include <TLG_Component_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
struct FPlayer_Response;
//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class TLGAME_API UTLG_Component_Dialogue : public UActorComponent
{
	GENERATED_BODY()

public:
	UTLG_Component_Dialogue();

	virtual void BeginPlay();
	virtual void TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *this_tick_function);
	
	void Dialogue_Start(const FName &row_id);
	void Dialogue_End();
	void Handle_Player_Decision(const FPlayer_Response &player_response);

};
//------------------------------------------------------------------------------------------------------------
