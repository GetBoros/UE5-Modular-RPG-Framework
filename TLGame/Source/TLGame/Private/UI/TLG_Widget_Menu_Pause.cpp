//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Menu_Pause.h>
#include <UI/TLG_Widget_Button.h>

#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Menu_Pause
void UTLG_Widget_Menu_Pause::NativeConstruct()
{
	Super::NativeConstruct();

    if (ensureMsgf(TLG_Widget_Button_Flow_Class, TEXT("Floating Text Class not setting up") ) != true)
        return;

    Init();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Menu_Pause::Init()
{
    UTLG_Widget_Button_Flow *tlg_widget_button;

    const FText text_game_exit = FText::FromString(TEXT("Exit Game") ) ;
    const FText text_game_restart = FText::FromString(TEXT("Restart Game") );
    const FText text_game_Continue = FText::FromString(TEXT("Continue Game") );

    VB_Button_Menu_Pause->ClearChildren();

    // 2.0. Add button Continue game
    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Continue, text_game_Continue);
    VB_Button_Menu_Pause->AddChild(tlg_widget_button);

    // 2.1. Add button restart game
    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Restart_Level, text_game_restart);
    VB_Button_Menu_Pause->AddChild(tlg_widget_button);

    // 2.2. Add button exit game
    tlg_widget_button = CreateWidget<UTLG_Widget_Button_Flow>(this, TLG_Widget_Button_Flow_Class);
    if (tlg_widget_button != 0)
        tlg_widget_button->Init(ETLG_Game_Flow_Option::Quit_Game, text_game_exit);
    VB_Button_Menu_Pause->AddChild(tlg_widget_button);

}
//------------------------------------------------------------------------------------------------------------
