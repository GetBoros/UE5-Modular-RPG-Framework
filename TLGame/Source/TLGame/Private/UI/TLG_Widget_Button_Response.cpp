//------------------------------------------------------------------------------------------------------------
#include "UI/TLG_Widget_Button_Response.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Response
void UTLG_Widget_Button_Response::NativeConstruct()
{
    Super::NativeConstruct();

    if (Button_Click == 0)
        return;

    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);
    Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Init(const FPlayer_Response& data, int32 index)
{
    Response_Index = index;

    if (Text_Response != 0)
        Text_Response->SetText(data.Response_Text);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Handle_Button_Clicked()
{
    if (Response_Index >= 0)
        On_Response_Clicked_Delegate.Broadcast(Response_Index);
}
//------------------------------------------------------------------------------------------------------------