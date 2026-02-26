//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stats_Bar.h>
#include <UI/TLG_Widget_Stat.h>
#include <UI/TLG_Widget_Controller.h>
//------------------------------------------------------------------------------------------------------------





// UTLG_Widget_Stats_Bar
void UTLG_Widget_Stats_Bar::On_Widget_Controller_Set_Implementation()
{
	UTLG_Widget_Controller *tlg_widget_controller;

	Super::On_Widget_Controller_Set_Implementation();

	tlg_widget_controller = Cast<UTLG_Widget_Controller>(GBUIC_Widget_Controller);
	tlg_widget_controller->On_Changed_Sanity.AddDynamic(this, &UTLG_Widget_Stats_Bar::Update_Sanity);
	tlg_widget_controller->On_Changed_Empathy.AddDynamic(this, &UTLG_Widget_Stats_Bar::Update_Empathy);
	tlg_widget_controller->On_Changed_Fatigued.AddDynamic(this, &UTLG_Widget_Stats_Bar::Update_Fatigued);
	tlg_widget_controller->On_Changed_Dominance.AddDynamic(this, &UTLG_Widget_Stats_Bar::Update_Dominance);

	tlg_widget_controller->Broadcast_Initial_Values();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Sanity(float new_value, float delta)
{
	TLG_Widget_Stat_Sanity->Update_Stat(new_value);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Empathy(float new_value, float delta)
{
	TLG_Widget_Stat_Empathy->Update_Stat(new_value);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Fatigued(float new_value, float delta)
{
	TLG_Widget_Stat_Fatigued->Update_Stat(new_value);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Dominance(float new_value, float delta)
{
	TLG_Widget_Stat_Dominance->Update_Stat(new_value);
}
//------------------------------------------------------------------------------------------------------------
