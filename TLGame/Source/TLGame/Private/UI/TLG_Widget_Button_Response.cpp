//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Button_Response.h>

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Materials/MaterialInstanceDynamic.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_Button_Response
void UTLG_Widget_Button_Response::NativeConstruct()
{
    Super::NativeConstruct();

    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);
    Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Init(const FPlayer_Response &player_response_data, const int32 index)
{
    Response_Index = index;
    TB_Response->SetText(player_response_data.Text_Response);
    
    Button_Update_Visuals(player_response_data.Category);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Button_Update_Visuals(EDialogue_Response_Category dialogue_response_category)
{
    UMaterialInterface *material_interface;
    FButtonStyle button_style = Button_Click->GetStyle();
    
    material_interface = Cast<UMaterialInterface>(button_style.Normal.GetResourceObject() );
    if (material_interface == 0)
        return;  // Not MI or M in UButton

    if (MID_Button == 0)  // Create MID, and set it to our button button_style
    {
        MID_Button = UMaterialInstanceDynamic::Create(material_interface, this);

        button_style.Normal.SetResourceObject(MID_Button);
        button_style.Hovered.SetResourceObject(MID_Button);
        button_style.Pressed.SetResourceObject(MID_Button);

        Button_Click->SetStyle(button_style);
    }

    if (MID_Button != 0)  // if material have param Color chenge it
        MID_Button->SetVectorParameterValue(FName("Color"), Get_Color_By_Category(dialogue_response_category) );
}
//------------------------------------------------------------------------------------------------------------
FLinearColor UTLG_Widget_Button_Response::Get_Color_By_Category(EDialogue_Response_Category dialogue_response_category) const
{
    switch (dialogue_response_category)
    {
    case EDialogue_Response_Category::Aggressive:
        return FLinearColor(0.8f, 0.1f, 0.1f, 1.0f); // Red
    case EDialogue_Response_Category::Submissive:  
        return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f); // Green
    case EDialogue_Response_Category::Logical:
        return FLinearColor(0.2f, 0.4f, 0.9f, 1.0f); // Blue
    case EDialogue_Response_Category::Silent:
        return FLinearColor(0.3f, 0.3f, 0.3f, 1.0f); // Grey
    default:
        return FLinearColor::White;
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Handle_Button_Clicked()
{
    if (Response_Index >= 0)
        On_Response_Clicked_Delegate.Broadcast(Response_Index);
}
//------------------------------------------------------------------------------------------------------------