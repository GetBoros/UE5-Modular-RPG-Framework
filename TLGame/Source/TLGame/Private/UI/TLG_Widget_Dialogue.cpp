//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Button_Response.h>
#include <UI/TLG_Typewriter_Text.h>
#include <System/TLG_Player_Controller.h>

#include <Materials/MaterialInstanceDynamic.h>

#include <Components/RetainerBox.h>
#include <Components/VerticalBox.h>
#include <Components/Button.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Dialogue
void UTLG_Widget_Dialogue::NativeConstruct()
{
    constexpr float distortion_power_effect = 0.005f;
	constexpr float linear_color_grey = 0.484f;
	constexpr float linear_color_white = 1.0f;

    Super::NativeConstruct();

    ensureMsgf(TLG_Widget_Button_Response_Class, TEXT("Need init add buttons to button container") );

    MID_Effect = RB_NPC_Line_Effect->GetEffectMaterial();  // Get dynamic material from retainer box

    Set_Text_Distortion(distortion_power_effect);
    Set_Text_Tint(FLinearColor(linear_color_white, linear_color_white, linear_color_white) );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Setup_Dialogue_Node(const FDialogue_Node &dialogue_node)
{
    UTLG_Widget_Button_Response *tlg_widget_button_response;

    Dialogue_Node_Current = dialogue_node;
    if (Dialogue_Node_Current.Text_Name_Speaker.IsEmpty() != true)
        TB_Speaker_Name->SetText(Dialogue_Node_Current.Text_Name_Speaker);
    
    TLG_Typewriter_Text_NPC_Line->Start_Typewriter(dialogue_node.Text_NPC_Line, 0.06f);  // 0.03f sec per char
    VB_TLG_Widget_Button_Response_Container->ClearChildren();  // clear all other child if need

    // Spawn TLG_Widget_Button_Response_Class and attach to VB_TLG_Widget_Button_Response_Container, and bind On_Clicked
    for (int32 i = 0; i < dialogue_node.Player_Responses.Num(); i++)
    {
        const FPlayer_Response &response = dialogue_node.Player_Responses[i];

        tlg_widget_button_response = CreateWidget<UTLG_Widget_Button_Response>(this, TLG_Widget_Button_Response_Class);

        tlg_widget_button_response->Init(response, i);
        tlg_widget_button_response->On_Response_Clicked_Delegate.AddDynamic(this, &UTLG_Widget_Dialogue::Handle_Response_Clicked);
     
        VB_TLG_Widget_Button_Response_Container->AddChild(tlg_widget_button_response);
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Set_Text_Distortion(const float value) const
{
    MID_Effect->SetScalarParameterValue(FName("Power"), value);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Set_Text_Tint(const FLinearColor &linear_color) const
{
    MID_Effect->SetVectorParameterValue(FName("Tint"), linear_color);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Handle_Response_Clicked(int32 response_index)
{
    if (Dialogue_Node_Current.Player_Responses.IsValidIndex(response_index) == false)
        return;

    On_Response_Selected(Dialogue_Node_Current.Player_Responses[response_index]);  // Visuals (BP)

    if (ATLG_Player_Controller *tlg_player_controller = Cast<ATLG_Player_Controller>(GetOwningPlayer() ) )
        tlg_player_controller->Handle_Player_Decision(Dialogue_Node_Current.Player_Responses[response_index]);  // Send data to player controller logic
}
//------------------------------------------------------------------------------------------------------------