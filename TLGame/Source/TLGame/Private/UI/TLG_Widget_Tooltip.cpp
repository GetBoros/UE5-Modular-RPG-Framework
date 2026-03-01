//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Tooltip.h>

#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------



// UTLG_Widget_Tooltip
void UTLG_Widget_Tooltip::NativeConstruct()
{
	Super::NativeConstruct();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Tooltip::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Tooltip::Update_TB_Description(const FText &description)
{
	TB_Description->SetText(description);
}
//------------------------------------------------------------------------------------------------------------
