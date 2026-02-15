//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Menu_Pause.h>
#include <UI/TLG_Widget_Button.h>
#include <UI/TLG_Widget_Controller.h>

#include <Components/VerticalBox.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Menu_Pause
void UTLG_Widget_Menu_Pause::NativeConstruct()
{
	Super::NativeConstruct();

    if (ensureMsgf(TLG_Widget_Button_Flow_Class, TEXT("No setting in BP") ) != true)
        return;

    VB_Button_Menu_Pause->ClearChildren();  // Clear designer stuff
    Text_Game_Over->SetVisibility(ESlateVisibility::Collapsed);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Menu_Pause::Init(ESlateVisibility visibility)
{
    SetVisibility(visibility);

    if (VB_Button_Menu_Pause->HasAnyChildren() == true)
        return;

    Add_Menu_Pause_Buttons(VB_Button_Menu_Pause);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Menu_Pause::Handle_Widget_Controller()
{
     if (UTLG_Widget_Controller *tlg_widget_controller = Cast<UTLG_Widget_Controller>(GBUIC_Widget_Controller) )
         tlg_widget_controller->On_Game_Over.AddUObject(this, &UTLG_Widget_Menu_Pause::Handle_Changed_Game_State);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Menu_Pause::Handle_Changed_Game_State()
{
    SetVisibility(ESlateVisibility::Visible);
    Text_Game_Over->SetVisibility(ESlateVisibility::Visible);

    if (VB_Button_Menu_Pause->HasAnyChildren() == true)
        return;

    Add_Menu_Pause_Buttons(VB_Button_Menu_Pause);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Menu_Pause::Add_Menu_Pause_Buttons(UVerticalBox *vertical_box)
{
    UTLG_Widget_Button_Flow *tlg_widget_button;

    const FText text_game_exit = FText::FromString(TEXT("Exit Game") );
    const FText text_game_restart = FText::FromString(TEXT("Restart Game") );
    const FText text_game_Continue = FText::FromString(TEXT("Continue Game") );

    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Continue, text_game_Continue);
    vertical_box->AddChild(tlg_widget_button);

    // 2.1. Add button restart game
    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Restart_Level, text_game_restart);
    vertical_box->AddChild(tlg_widget_button);

    // 2.2. Add button exit game
    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Quit_Game, text_game_exit);
    vertical_box->AddChild(tlg_widget_button);

}
//------------------------------------------------------------------------------------------------------------
