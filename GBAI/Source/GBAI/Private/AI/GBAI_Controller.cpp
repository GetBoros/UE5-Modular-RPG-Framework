//------------------------------------------------------------------------------------------------------------
#include <AI/GBAI_Controller.h>
#include <AI/GBAI_Types.h>
#include <Subsystems/GBEventBusSubsystem.h>

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
	Super::BeginPlay();

	UGBEventBusSubsystem *eventbussubsystem = GetGameInstance()->GetSubsystem<UGBEventBusSubsystem>();
	if (eventbussubsystem != 0)
		eventbussubsystem->OnEventDispatched.AddDynamic(this, &AGBAI_Controller::Handle_Game_Event);  // Sub to delegate
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Controller::Handle_Game_Event(FGameplayTag event_tag, const UObject *payload)
{
	int yy = 0;

	if (event_tag.MatchesTag(FGameplayTag::RequestGameplayTag("Food.Sugar") ) )  // Filter
	{
		if (payload == GetPawn() )
			yy++;
	}
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
	state_tree_event.Origin = TEXT("BOROS MOLODEC");//GetFName();
	state_tree_event.Payload = instanced_struct;
	state_tree_event.Tag = gameplay_tag;

	AI_State_Tree->SendStateTreeEvent(state_tree_event);
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
