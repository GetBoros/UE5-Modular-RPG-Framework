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

    ensureMsgf(Button_Response_Class, TEXT("Need init add buttons to button container") );

	Effect_Material = RB_NPC_Line_Effect->GetEffectMaterial();  // Get dynamic material from retainer box

    Set_Text_Distortion(distortion_power_effect);
    Set_Text_Tint(FLinearColor(linear_color_white, linear_color_white, linear_color_white) );
    
    Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Setup_Dialogue_Node(const FDialogue_Node &node_data)
{
    UUserWidget *button_response_widget;
    UTLG_Widget_Button_Response *button_response;

    Current_Node = node_data;

    Text_NPC_Line->Start_Typewriter(node_data.NPC_Line, 0.06f);  // 0.03f sec per char
    Text_Speaker_Name->SetText(FText::FromString("Kate") );
    VB_Buttons_Response_Container->ClearChildren();  // clear all other child if need

    for (int32 i = 0; i < node_data.Player_Responses.Num(); i++)  // Spawn Button_Response_Class and attach to VB_Buttons_Response_Container, and bind On_Clicked
    {
        const FPlayer_Response &response = node_data.Player_Responses[i];

        button_response_widget = CreateWidget<UUserWidget>(this, Button_Response_Class);
        button_response = Cast<UTLG_Widget_Button_Response>(button_response_widget);

        button_response->Init(response, i);
        button_response->On_Response_Clicked_Delegate.AddDynamic(this, &UTLG_Widget_Dialogue::Handle_Response_Clicked);
     
        VB_Buttons_Response_Container->AddChild(button_response);
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Set_Text_Distortion(const float value) const
{
    Effect_Material->SetScalarParameterValue(FName("Power"), value);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Set_Text_Tint(const FLinearColor &linear_color) const
{
    Effect_Material->SetVectorParameterValue(FName("Tint"), linear_color);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Dialogue::Handle_Response_Clicked(int32 response_index)
{
    if (Current_Node.Player_Responses.IsValidIndex(response_index) == false)
        return;

    On_Response_Selected(Current_Node.Player_Responses[response_index]);  // Visuals (BP)

    if (ATLG_Player_Controller *tlg_player_controller = Cast<ATLG_Player_Controller>(GetOwningPlayer() ) )
        tlg_player_controller->Handle_Player_Decision(Current_Node.Player_Responses[response_index]);  // Send data to player controller logic
}
//------------------------------------------------------------------------------------------------------------