//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Button_Navigation.h>
#include <System/TLG_Player_Controller.h>

#include <Components/Button.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Navigation
void UTLG_Widget_Button_Navigation::NativeConstruct()
{
    Super::NativeConstruct();

    if (Button_Click == 0)
        return;
 
    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button_Navigation::Handle_Click);
    Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button_Navigation::Handle_Click);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Navigation::Init(const FTLG_Location_Exit &exit_data)
{
    const FText text_button = exit_data.Text_Button;
    Target_Location = exit_data.TLG_Data_Location_Target;

    if (text_button.IsEmpty() == true)
        TB_Loction_Name->SetText(FText::FromString(FString(L"Empty No Name in UTLG_Data_Location DA") ) );
    else
        TB_Loction_Name->SetText(text_button);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Navigation::Init(const FTLG_Location_Action &tlg_location_action)
{
    const int time_cost_minutes = tlg_location_action.Time_Cost_Minutes;
    const FText text_button = tlg_location_action.Text_Button;
    const FText text_format_pattern = FText::FromString("{0} ({1})");
    const FText text_time = Format_Time_From_Minutes(time_cost_minutes);
    const FText text_final = FText::Format(text_format_pattern, text_button, text_time);

    Gameplay_Tag_Action = tlg_location_action.Gameplay_Tag_Action;

    if (text_button.IsEmpty() == true)
        TB_Loction_Name->SetText(FText::FromString(FString(L"Empty No Name in UTLG_Data_Location DA") ) );
    else
        TB_Loction_Name->SetText(text_final);
}
//------------------------------------------------------------------------------------------------------------
FText UTLG_Widget_Button_Navigation::Format_Time_From_Minutes(int32 minutes_cost) const
{
    const int32 minutes_in_month = 43200;
    const int32 minutes_in_hour = 60;
    const int32 minutes_in_day = 1440;

    if (minutes_cost >= minutes_in_month && (minutes_cost % minutes_in_month == 0) )
        return FText::Format(FText::FromString("{0}mon"), FText::AsNumber(minutes_cost / minutes_in_month) );

    if (minutes_cost >= minutes_in_day && (minutes_cost % minutes_in_day == 0) )
        return FText::Format(FText::FromString("{0}d"), FText::AsNumber(minutes_cost / minutes_in_day) );

    if (minutes_cost >= minutes_in_hour && (minutes_cost % minutes_in_hour == 0) )
        return FText::Format(FText::FromString("{0}h"), FText::AsNumber(minutes_cost / minutes_in_hour) );

    return FText::Format(FText::FromString("{0}min"), FText::AsNumber(minutes_cost) );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Navigation::Handle_Click()
{
    ATLG_Player_Controller *tlg_player_controller;
    APlayerController *player_controller;

    if (Gameplay_Tag_Action.MatchesTag(FGameplayTag::RequestGameplayTag(TEXT("Test.StateTree.Tag3") ) ) )  // 
    {
        int yy = 0;
    }

    if (Target_Location == 0)
        return;

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    tlg_player_controller = Cast<ATLG_Player_Controller>(player_controller);
    if (tlg_player_controller != 0)
        tlg_player_controller->Move_To_Location(Target_Location);
}
//------------------------------------------------------------------------------------------------------------