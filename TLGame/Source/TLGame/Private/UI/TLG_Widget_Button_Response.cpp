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

    if (Button_Click == 0)
        return;

    Button_Click->OnClicked.RemoveDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);
    Button_Click->OnClicked.AddDynamic(this, &UTLG_Widget_Button_Response::Handle_Button_Clicked);

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Init(const FPlayer_Response &data, int32 index)
{
    Response_Index = index;

    if (Text_Response != 0)
        Text_Response->SetText(data.Text_Response);

    
    if (Button_Click == 0)
        return;

    Button_Update_Visuals(data.Category);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Button_Response::Button_Update_Visuals(EDialogue_Response_Category category)
{
    UMaterialInterface *base_mat;
    FButtonStyle style = Button_Click->GetStyle();
    
    base_mat = Cast<UMaterialInterface>(style.Normal.GetResourceObject());
    if (base_mat == 0)
        return;  // Not MI or M in UButton

    if (Button_Material == 0)  // Create MID, and set it to our button style
    {
        Button_Material = UMaterialInstanceDynamic::Create(base_mat, this);

        style.Normal.SetResourceObject(Button_Material);
        style.Hovered.SetResourceObject(Button_Material);
        style.Pressed.SetResourceObject(Button_Material);

        Button_Click->SetStyle(style);
    }

    if (Button_Material != 0)  // if material have param Color chenge it
        Button_Material->SetVectorParameterValue(FName("Color"), Get_Color_By_Category(category) );
}
//------------------------------------------------------------------------------------------------------------
FLinearColor UTLG_Widget_Button_Response::Get_Color_By_Category(EDialogue_Response_Category category) const
{
    switch (category)
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