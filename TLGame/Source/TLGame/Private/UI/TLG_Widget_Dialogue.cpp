//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Button_Response.h>
#include <System/TLG_Player_Controller.h>

#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Components/Button.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Dialogue
void UTLG_Widget_Dialogue::Setup_Dialogue_Node(const FDialogue_Node &node_data)
{
    UUserWidget *button_response_widget;
    UTLG_Widget_Button_Response *button_response;

    Current_Node = node_data;

    if (Text_NPC_Line != 0)
        Text_NPC_Line->SetText(node_data.NPC_Line);  // Set npc text line
    
    if (Buttons_Response_Container != 0)
        Buttons_Response_Container->ClearChildren();  // clear all other child if need

    if (Button_Response_Class == 0 || Buttons_Response_Container == 0)
        return;

    for (int32 i = 0; i < node_data.Player_Responses.Num(); i++)  // Spawn Button_Response_Class and attach to Buttons_Response_Container, and bind On_Clicked
    {
        const FPlayer_Response &response = node_data.Player_Responses[i];

        button_response_widget = CreateWidget<UUserWidget>(this, Button_Response_Class);
        button_response = Cast<UTLG_Widget_Button_Response>(button_response_widget);
        if (button_response != 0)
        {
            button_response->Init(response, i);
            button_response->On_Response_Clicked_Delegate.AddDynamic(this, &UTLG_Widget_Dialogue::Handle_Response_Clicked);
            
            Buttons_Response_Container->AddChild(button_response);
        }
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Handle_Response_Clicked(int32 response_index)
{
    APlayerController *player_controller;
    ATLG_Player_Controller *tlg_player_controller;

    if (Current_Node.Player_Responses.IsValidIndex(response_index) == false)
        return;

    On_Response_Selected(Current_Node.Player_Responses[response_index]);  // Visuals (BP)

    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    tlg_player_controller = Cast<ATLG_Player_Controller>(player_controller);
    if (tlg_player_controller != 0)
        tlg_player_controller->Process_Player_Decision(Current_Node.Player_Responses[response_index]);  // Send data to controller logic
}
//------------------------------------------------------------------------------------------------------------