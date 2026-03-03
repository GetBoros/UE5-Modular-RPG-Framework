//------------------------------------------------------------------------------------------------------------
#include <AI/GBAI_Controller.h>
#include <AI/GBAI_Types.h>
#include <Subsystems/GBC_Gameplay_Message_Subsystem.h>

#include <Components/StateTreeAIComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGBAI_Controller 
AGBAI_Controller ::AGBAI_Controller ()
 : Target_Actor(0), AI_State_Tree(0), AI_Perception(0), AI_Sense_Config_Sight(0)
{
	AI_State_Tree = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent") );
	AI_Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception") );
	AI_Sense_Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfigSight") );

	AI_Sense_Config_Sight->SightRadius = 2000.0f;
	AI_Sense_Config_Sight->LoseSightRadius = 2500.0f;
	AI_Sense_Config_Sight->PeripheralVisionAngleDegrees = 90.0f;
	AI_Sense_Config_Sight->SetMaxAge(5.0f);
	AI_Sense_Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AI_Sense_Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AI_Sense_Config_Sight->DetectionByAffiliation.bDetectFriendlies = false;

	SetGenericTeamId(FGenericTeamId(ETeamAttitude::Friendly) );

	AI_Perception->ConfigureSense(*AI_Sense_Config_Sight);
	AI_Perception->SetDominantSense(AI_Sense_Config_Sight->GetSenseImplementation() );
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller ::BeginPlay()
{
	UGBC_Gameplay_Message_Subsystem *gameplay_message_subsystem;
	FGameplayTag tag_sugar = FGameplayTag::RequestGameplayTag("Food.Sugar");  // if has tag, get ref
	auto callback_on_is_tag_sugar = [this](FGameplayTag tag, const UObject *payload) { this->On_Is_Tag_Sugar(tag, payload); };

	Super::BeginPlay();

	gameplay_message_subsystem = GetGameInstance()->GetSubsystem<UGBC_Gameplay_Message_Subsystem>();
	if (gameplay_message_subsystem == 0)
		return;

	gameplay_message_subsystem->On_Event_Dispatched.AddDynamic(this, &AGBAI_Controller::Handle_Game_Event);  // Sub to delegate
	Handle_Listener_On_Is_Tag_Sugar = gameplay_message_subsystem->Register_Listener(tag_sugar, callback_on_is_tag_sugar);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGBC_Gameplay_Message_Subsystem *gameplay_message_subsystem;
	FGameplayTag tag_sugar = FGameplayTag::RequestGameplayTag("Food.Sugar");

	gameplay_message_subsystem = GetGameInstance()->GetSubsystem<UGBC_Gameplay_Message_Subsystem>();  // Unsub
	if (gameplay_message_subsystem != 0)
		gameplay_message_subsystem->Unregister_Listener(tag_sugar, Handle_Listener_On_Is_Tag_Sugar);

	Super::EndPlay(EndPlayReason);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller::Handle_Game_Event(FGameplayTag event_tag, const UObject *payload)
{
	int32 yy = 0;

	if (event_tag.MatchesTag(FGameplayTag::RequestGameplayTag("Food.Sugar") ) )  // Filter
		if (payload == GetPawn() )
			yy++;  // !!! TEMP EXAMPLE
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller ::OnPossess(APawn *in_pawn)
{
	Super::OnPossess(in_pawn);

	AI_State_Tree->StartLogic();
	AI_Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AGBAI_Controller ::On_Target_Perception_Updated);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller ::Set_Patrol_Data(const float patrol_radius, const FVector patrol_center_location)
{
	Patrol_Radius = patrol_radius;
	Patrol_Center_Location = patrol_center_location;
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller ::Send_State_Tree_Event(const FGameplayTag gameplay_tag)
{// Example

	FSGBAI_Payload_Test payload_test;
	FStateTreeEvent state_tree_event;
	FInstancedStruct instanced_struct;

	instanced_struct = FInstancedStruct::Make(payload_test);
	state_tree_event.Origin = TEXT("BOROS MOLODEC");
	state_tree_event.Payload = instanced_struct;
	state_tree_event.Tag = gameplay_tag;

	AI_State_Tree->SendStateTreeEvent(state_tree_event);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller::On_Is_Tag_Sugar(FGameplayTag tag, const UObject *payload)
{
	int32 yy = 0;
	yy++;
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller ::On_Target_Perception_Updated(AActor *actor, FAIStimulus stimulus)
{
	return;

	const FGameplayTag sended_tag = FGameplayTag::RequestGameplayTag(TEXT("Test.StateTree.Tag3") );  // !!! TEMP TEST

	if (stimulus.WasSuccessfullySensed() == true)
	{
		if (IsValid(Target_Actor) == true)  // if has target why we should change it?
			return;

		Target_Actor = actor;

		SetFocus(Target_Actor);
		Send_State_Tree_Event(sended_tag);  // !!! TEMP | Send event to start chasing || FInstancedStruct::Make(Custom_UStruct_Payload_Data);
	}
	else if (Target_Actor == actor)
	{
		ClearFocus(EAIFocusPriority::Default);
		Target_Actor = 0;
	}
}
//------------------------------------------------------------------------------------------------------------
