//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stats_Bar.h>
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Stat.h>
#include <UI/TLG_Widget_Controller.h>
#include <UI/TLG_Widget_Text_Floating.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------





// UTLG_Widget_Stats_Bar
void UTLG_Widget_Stats_Bar::On_Widget_Controller_Set_Implementation()
{
	UTLG_Widget_Controller *tlg_widget_controller;

	Super::On_Widget_Controller_Set_Implementation();

	tlg_widget_controller = Cast<UTLG_Widget_Controller>(GBUIC_Widget_Controller);

	tlg_widget_controller->On_Changed_Sanity.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Sanity);
	tlg_widget_controller->On_Changed_Empathy.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Empathy);
	tlg_widget_controller->On_Changed_Fatigued.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Fatigued);
	tlg_widget_controller->On_Changed_Dominance.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Dominance);

	tlg_widget_controller->On_Changed_Time_Game.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Time_Game);
	tlg_widget_controller->On_Changed_Day.AddUObject(this, &UTLG_Widget_Stats_Bar::Update_Day);  // !!! TEMP Remove END

	tlg_widget_controller->Broadcast_Initial_Values();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Time_Game(int32 hours, int32 minutes)
{
	FString time_str = FString::Printf(TEXT("%02d:%02d"), hours, minutes);

	Text_Clock->SetText(FText::FromString(time_str) );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Day(int32 current_day)
{
    FString day_str = FString::Printf(TEXT("Day %d"), current_day);

    Text_Day_Counter->SetText(FText::FromString(day_str) );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Sanity(float new_value, float delta)
{
	TLG_Widget_Stat_Sanity->Update_Stat(new_value);

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Text_Floating(delta, FText::FromString("Sanity") );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Empathy(float new_value, float delta)
{
	TLG_Widget_Stat_Empathy->Update_Stat(new_value);

	if (FMath::IsNearlyZero(delta) != true)
        Spawn_Text_Floating(delta, FText::FromString("Empathy") );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Fatigued(float new_value, float delta)
{
	TLG_Widget_Stat_Fatigued->Update_Stat(new_value);

	if (FMath::IsNearlyZero(delta) != true)
        Spawn_Text_Floating(delta, FText::FromString("Fatigued") );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Update_Dominance(float new_value, float delta)
{
	TLG_Widget_Stat_Dominance->Update_Stat(new_value);

	if (FMath::IsNearlyZero(delta) != true)
		Spawn_Text_Floating(delta, FText::FromString("Dominance") );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stats_Bar::Spawn_Text_Floating(const float delta, const FText& name_text)
{
	UTLG_Widget_Text_Floating *tlg_widget_text_floating;

    tlg_widget_text_floating = CreateWidget<UTLG_Widget_Text_Floating>(this, TLG_Widget_Text_Floating_Class);
    if (tlg_widget_text_floating == 0)
        return;

    FString string_sign = (delta > 0) ? TEXT("+") : TEXT("");
    FText text_final = FText::FromString(FString::Printf(TEXT("%s%d %s"), *string_sign, FMath::RoundToInt(delta), *name_text.ToString() ) );
    FLinearColor linear_color = (delta > 0) ? FLinearColor::Green : FLinearColor::Red;  // !!! TEMP can change if dominance to swap color
    
    tlg_widget_text_floating->Setup_Visuals(text_final, linear_color);
    
	VB_Text_Floating_Events->AddChild(tlg_widget_text_floating);

}
//------------------------------------------------------------------------------------------------------------
