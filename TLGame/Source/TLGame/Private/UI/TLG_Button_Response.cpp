//------------------------------------------------------------------------------------------------------------
#include "UI/TLG_Button_Response.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Button_Response
void UTLG_Button_Response::NativeConstruct()
{
    Super::NativeConstruct();

    if (Btn_Click == 0)
        return;

    Btn_Click->OnClicked.RemoveDynamic(this, &UTLG_Button_Response::Handle_Button_Clicked);
    Btn_Click->OnClicked.AddDynamic(this, &UTLG_Button_Response::Handle_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Button_Response::Init(const FPlayer_Response& data, int32 index)
{
    Response_Index = index;

    if (Text_Response != 0)
        Text_Response->SetText(data.Response_Text);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Button_Response::Handle_Button_Clicked()
{
    if (Response_Index >= 0)
        On_Response_Clicked_Delegate.Broadcast(Response_Index);
}
//------------------------------------------------------------------------------------------------------------