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
void UTLG_Widget_Button_Navigation::Handle_Click()
{
    ATLG_Player_Controller *tlg_player_controller;
    APlayerController *player_controller;

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