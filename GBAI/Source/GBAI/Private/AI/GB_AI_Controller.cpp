//------------------------------------------------------------------------------------------------------------
#include <AI/GB_AI_Controller.h>
#include <AI/GB_AI_Types.h>

#include <Components/StateTreeAIComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionComponent.h>
//------------------------------------------------------------------------------------------------------------




// AGB_AI_Controller
AGB_AI_Controller::AGB_AI_Controller()
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
void AGB_AI_Controller::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Controller::OnPossess(APawn* in_pawn)
{
	Super::OnPossess(in_pawn);

	AI_State_Tree->StartLogic();
	AI_Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AGB_AI_Controller::On_Target_Updated);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Controller::Set_Patrol_Data(const float patrol_radius, const FVector patrol_center_location)
{
	Patrol_Radius = patrol_radius;
	Patrol_Center_Location = patrol_center_location;
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Controller::Send_State_Tree_Event(const FGameplayTag gameplay_tag)
{// Example

	FSGB_AI_Payload_Test payload_test;
	FStateTreeEvent state_tree_event;
	FInstancedStruct instanced_struct;

	instanced_struct = FInstancedStruct::Make(payload_test);
	state_tree_event.Origin = TEXT("BOROS MOLODEC");//GetFName();
	state_tree_event.Payload = instanced_struct;
	state_tree_event.Tag = gameplay_tag;

	AI_State_Tree->SendStateTreeEvent(state_tree_event);
}
//------------------------------------------------------------------------------------------------------------
void AGB_AI_Controller::On_Target_Updated(AActor* actor, FAIStimulus stimulus)
{
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
