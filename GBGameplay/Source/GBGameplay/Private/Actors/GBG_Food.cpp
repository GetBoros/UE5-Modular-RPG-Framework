//------------------------------------------------------------------------------------------------------------
#include <Actors/GBG_Food.h>
#include <Components/GBG_Item_Data.h>
#include <Subsystems/GBG_Food_Subsystem.h>
//------------------------------------------------------------------------------------------------------------




// AGBG_Food
AGBG_Food::AGBG_Food()
{
	PrimaryActorTick.bCanEverTick = false;

	Item_Data_Component = CreateDefaultSubobject<UGBG_Item_Data>(TEXT("ItemDataComponent") );
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::BeginPlay()
{
	Super::BeginPlay();

    if (UWorld *world = GetWorld() )
    {
        if (UGBG_Food_Subsystem *food_sys = world->GetSubsystem<UGBG_Food_Subsystem>() )
            food_sys->Register(this);
    }
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::EndPlay(const EEndPlayReason::Type end_play_reason)
{
    if (UWorld *world = GetWorld() )
    {
        if (UGBG_Food_Subsystem *food_sys = world->GetSubsystem<UGBG_Food_Subsystem>() )
            food_sys->Unregister(this);
    }

    Super::EndPlay(end_play_reason);
}
//------------------------------------------------------------------------------------------------------------
void AGBG_Food::Tick(float delta_time)
{
	Super::Tick(delta_time);
}
//------------------------------------------------------------------------------------------------------------
