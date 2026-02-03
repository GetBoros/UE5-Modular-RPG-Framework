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




//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::NativeConstruct()
{
    Super::NativeConstruct();

    if (Button_Click != 0)
    {
        Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button::Handle_Click_Internal);
        Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button::Handle_Click_Internal);
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::On_Click_Action()
{
    // Базовая реализация пустая (или лог)
    UE_LOG(LogTemp, Warning, TEXT("Base Button Clicked - No Logic Implemented") );

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Handle_Click_Internal()
{
    On_Click_Action();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button::Set_Button_Text(const FText& text)
{
    if (TB_Location_Name != 0)
    {
        TB_Location_Name->SetText(text);
    }
}
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Action
void UTLG_Widget_Button_Action::Init(const FTLG_Location_Action& action_data)
{
    Action_Tag = action_data.Gameplay_Tag_Action;
    Time_Cost_Minutes = action_data.Time_Cost_Minutes;

    FText time_text = Format_Time_From_Minutes(Time_Cost_Minutes);
    FText final_text = FText::Format(FText::FromString("{0} ({1})"), action_data.Text_Button, time_text);

    Set_Button_Text(final_text);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Action::On_Click_Action()
{
    // Тут мы вызываем метод контроллера для действий
    APlayerController* pc = GetOwningPlayer();
    if (pc == 0)
        return;

    ATLG_Player_Controller* tlg_pc = Cast<ATLG_Player_Controller>(pc);
    if (tlg_pc != 0)
    {
        int yy = 0;
        // Тебе нужно будет создать этот метод в контроллере!
        //tlg_pc->Execute_Action(Action_Tag, Time_Cost_Minutes);
    }
}
//------------------------------------------------------------------------------------------------------------
FText UTLG_Widget_Button_Action::Format_Time_From_Minutes(int32 minutes_cost) const
{
    const int32 minutes_in_month = 43200;
    const int32 minutes_in_hour = 60;
    const int32 minutes_in_day = 1440;

    if (minutes_cost >= minutes_in_month && (minutes_cost % minutes_in_month == 0))
        return FText::Format(FText::FromString("{0}mon"), FText::AsNumber(minutes_cost / minutes_in_month));

    if (minutes_cost >= minutes_in_day && (minutes_cost % minutes_in_day == 0))
        return FText::Format(FText::FromString("{0}d"), FText::AsNumber(minutes_cost / minutes_in_day));

    if (minutes_cost >= minutes_in_hour && (minutes_cost % minutes_in_hour == 0))
        return FText::Format(FText::FromString("{0}h"), FText::AsNumber(minutes_cost / minutes_in_hour));

    return FText::Format(FText::FromString("{0}min"), FText::AsNumber(minutes_cost));
}
//------------------------------------------------------------------------------------------------------------
