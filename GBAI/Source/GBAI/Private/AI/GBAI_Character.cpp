//------------------------------------------------------------------------------------------------------------
#include <AI/GBAI_Character.h>
#include <AI/GBAI_Controller.h>
#include "Settings/GBAI_Settings.h" 
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
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::Tick(float delta_time)
{
	Super::Tick(delta_time);

	// Получаем доступ к настройкам (это очень быстро, так как CDO уже в памяти)
	const UGBAI_Settings* ai_settings = GetDefault<UGBAI_Settings>();

	if (ai_settings != 0)
	{
		//// Применяем глобальный множитель
		//const float final_hunger_rate = Base_Hunger_Rate * ai_settings->Global_Hunger_Multiplier;

		//Current_Hunger += final_hunger_rate * delta_time;

		//// Если включен дебаг - рисуем
		//if (ai_settings->Draw_Debug_Hunger == true)
		//{
		//	// Тут можно вызвать твой метод отрисовки дебага
		//	// Draw_Hunger_Debug(); 
		//}
	}
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	//AI_Stat_Component->On_Changed_Stamina.RemoveDynamic(this, &AGBAI_Character::On_Stamina_Changed);

	Super::EndPlay(end_play_reason);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::PossessedBy(AController *controller)
{
	Super::PossessedBy(controller);

	AI_Controller = Cast<AGBAI_Controller>(controller);
	//if (IsValid(AI_Controller) == true)
	//	AI_Controller->On_AI_Action_Requested.AddDynamic(this, &AGBAI_Character::Handle_On_AI_Action_Requested);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::UnPossessed()
{
	if (AI_Controller != 0)
	//	AI_Controller->On_AI_Action_Requested.RemoveDynamic(this, &AGBAI_Character::Handle_On_AI_Action_Requested);
	//AI_Controller = 0;

	Super::UnPossessed();
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::SetupPlayerInputComponent(UInputComponent *player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);
}
//------------------------------------------------------------------------------------------------------------
void AGBAI_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//AI_Stat_Component->On_Changed_Stamina.AddDynamic(this, &AGBAI_Character::On_Stamina_Changed);  // !!! TEMP
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
