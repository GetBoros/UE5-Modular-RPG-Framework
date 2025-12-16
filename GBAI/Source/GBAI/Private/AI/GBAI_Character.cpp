//------------------------------------------------------------------------------------------------------------
#include <AI/GBAI_Character.h>
#include <AI/GBAI_Controller.h>

#include <Subsystems/GBC_Gameplay_Message_Subsystem.h>
#include <Settings/GBAI_Settings.h>

#include <Engine/AssetManager.h>
#include <Components/GameFrameworkComponentManager.h>
#include <VisualLogger/VisualLogger.h>
//------------------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY_STATIC(LogGBAI, Log, All);
//------------------------------------------------------------------------------------------------------------




// AGBAI_Character
AGBAI_Character::AGBAI_Character()
 : AI_Controller(0)
{
	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::BeginPlay()
{
	UGBC_Gameplay_Message_Subsystem *event_bus_subsystem;
	UAssetManager &asset_manager = UAssetManager::Get();
	FPrimaryAssetType item_asset_type("Item");
	TArray<FPrimaryAssetId> asset_id_list;

	Super::BeginPlay();
	AI_Settings = GetDefault<UGBAI_Settings>();  // !!! EXAMPLES Project Settings
	Spawn_Loot(FGameplayTag::RequestGameplayTag(FName("Food.Apple") ) );  // !!! EXAMPLES SoftObjectPtr Example
	event_bus_subsystem = GetGameInstance()->GetSubsystem<UGBC_Gameplay_Message_Subsystem >();  // !!! TEMP EXAMPLES 
	asset_manager.GetPrimaryAssetIdList(item_asset_type, asset_id_list);

	if (event_bus_subsystem != 0)
		event_bus_subsystem->Broadcast_Message(FGameplayTag::RequestGameplayTag("Food.Sugar"), this);  // !!! TEMP Example better struct or payload interface

	// !!! TEMP EXAMPLE Data Driven Example
	if (asset_id_list.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("=== Found %d items registered in Asset Manager! ==="), asset_id_list.Num() );

		for (const FPrimaryAssetId &asset_id : asset_id_list)
			UE_LOG(LogTemp, Log, TEXT("  - Found Item: %s"), *asset_id.ToString() );
	}
	else
		UE_LOG(LogTemp, Error, TEXT("=== No items found! Check Asset Manager settings and paths. ===") );
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::Tick(float delta_time)
{
	constexpr float food_low_value = 20.0f;

	Super::Tick(delta_time);
	
	if (Get_Hunger() < food_low_value)
	{
		const FVector head_location = GetActorLocation() + FVector(0, 0, 90);
		
		UE_VLOG_LOCATION(this, LogGBAI, Warning, head_location, 30.0f, FColor::Red, TEXT("Low Food!") );
	}

	if (AI_Settings != 0)
	{
		const float final_hunger_rate = 1.0f * AI_Settings->Global_Hunger_Multiplier;  // Apply global multiplier
		const float hunger = Get_Hunger() + final_hunger_rate * delta_time;

		if (AI_Settings->Draw_Debug_Hunger == true)
			int yy = 0;  // Can add some debug visualisation
	}

	UE_VLOG(this, LogGBAI, Log, TEXT("Hunger: %.2f | State: %s"), Get_Hunger(), TEXT("Roaming") );  // !!! EXAMPLES Visual Logger
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(end_play_reason);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::PossessedBy(AController *controller)
{
	Super::PossessedBy(controller);

	AI_Controller = Cast<AGBAI_Controller>(controller);
	if (IsValid(AI_Controller) == true)
		AI_Controller->On_AI_Action_Requested.AddDynamic(this, &AGBAI_Character::Spawn_Loot);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::UnPossessed()
{
	if (AI_Controller != 0)
		AI_Controller->On_AI_Action_Requested.RemoveDynamic(this, &AGBAI_Character::Spawn_Loot);
	
	AI_Controller = 0;

	Super::UnPossessed();
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
//------------------------------------------------------------------------------------------------------------
FGenericTeamId AGBAI_Character::GetGenericTeamId() const
{
	return ETeamAttitude::Friendly;
}
//------------------------------------------------------------------------------------------------------------
float AGBAI_Character::Get_Hunger() const
{
	return 10.0f;
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::Spawn_Loot(const FGameplayTag &requested_action_tag)
{
	FRotator spawn_rot = GetActorRotation();
	FVector spawn_loc = GetActorLocation() + FVector(0, 0, 50);
	UClass *class_to_spawn;

	if (Loot_Item_Class.IsNull() == true)
		return;  // If empty slot

	class_to_spawn = Loot_Item_Class.Get();  // If loaded class_to_spawn is valid
	if (class_to_spawn == 0)
		class_to_spawn = Loot_Item_Class.LoadSynchronous();  // If not loaded load()
	if (class_to_spawn == 0)
		return;

	GetWorld()->SpawnActor<AActor>(class_to_spawn, spawn_loc, spawn_rot);

	UE_LOG(LogTemp, Log, TEXT("Loot Spawned via Soft Reference!") );
}
//------------------------------------------------------------------------------------------------------------
