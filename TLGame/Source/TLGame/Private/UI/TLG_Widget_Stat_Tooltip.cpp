//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_Stat_Tooltip.h>

#include <Components/TextBlock.h>
//------------------------------------------------------------------------------------------------------------



// UTLG_Widget_Stat_Tooltip
void UTLG_Widget_Stat_Tooltip::NativeConstruct()
{
	Super::NativeConstruct();

}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat_Tooltip::NativePreConstruct()
{
	Super::NativePreConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_Stat_Tooltip::Update_TB_Description(const FText &description)
{
	TB_Description->SetText(description);
}
//------------------------------------------------------------------------------------------------------------
