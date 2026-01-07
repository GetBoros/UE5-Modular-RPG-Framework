//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Dialogue_Widget.h>
#include <UI/TLG_Button_Response.h>

#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Components/Button.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Dialogue_Widget
void UTLG_Dialogue_Widget::Setup_Dialogue_Node(const FDialogue_Node &node_data)
{
    UUserWidget *new_button;
    UTLG_Button_Response *btn;

    Current_Node = node_data;

    if (Text_NPC_Line != 0)
        Text_NPC_Line->SetText(node_data.NPC_Line);  // 1. Устанавливаем текст врага

    
    if (Container_Response_Buttons != 0)
        Container_Response_Buttons->ClearChildren();  // 2. Чистим старые кнопки (если были)

    if (Response_Button_Class == 0 && Container_Response_Buttons == 0)
        return;

    for (int32 i = 0; i < node_data.Player_Responses.Num(); ++i)  // 3. Спавним новые кнопки
    {
        const FPlayer_Response &response = node_data.Player_Responses[i];

        new_button = CreateWidget<UUserWidget>(this, Response_Button_Class);
        btn = Cast<UTLG_Button_Response>(new_button);

        if (btn != 0)
        {
            btn->Init(response, i);
            btn->On_Response_Clicked_Delegate.AddDynamic(this, &UTLG_Dialogue_Widget::Handle_Response_Clicked);
            
            Container_Response_Buttons->AddChild(btn);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Dialogue_Widget::Handle_Response_Clicked(int32 response_index)
{
    if (Current_Node.Player_Responses.IsValidIndex(response_index) )
        On_Response_Selected(Current_Node.Player_Responses[response_index]);  // Сообщаем блюпринтам или системе, что выбор сделан
}
//------------------------------------------------------------------------------------------------------------