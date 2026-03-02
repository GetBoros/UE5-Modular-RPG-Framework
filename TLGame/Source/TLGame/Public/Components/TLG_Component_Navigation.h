//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Components/ActorComponent.h>

#include <TLG_Component_Navigation.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOn_Location_Enter);
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Game_State;
class UTLG_Data_Enemy;
class UTLG_Data_Location;
class UAudioComponent;

struct FTLG_Location_Enemy;
struct FGameplayTagQuery;
//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class TLGAME_API UTLG_Component_Navigation : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTLG_Component_Navigation();

	virtual void BeginPlay();

	void Init(ATLG_HUD *tlg_hud, ATLG_Game_State *tlg_game_state);

    void Location_Enter();

    void Set_Location_Current(UTLG_Data_Location *tlg_data_location);

    UTLG_Data_Location *Get_Location_Current();
    UTLG_Data_Enemy *Get_Location_Data_Enemy();

    FOn_Location_Enter On_Location_Enter;

private:
    void Temp(const FGameplayTagQuery &spawn_conditions_tag_query, TSubclassOf<AActor> enemy_class);
    void Play_Ambient_Sound(USoundBase *sound_base_to_play);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_HUD> TLG_HUD;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<ATLG_Game_State> TLG_Game_State;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Location> TLG_Data_Location_Current;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UAudioComponent> Audio_Component_Ambient;

};
//------------------------------------------------------------------------------------------------------------
