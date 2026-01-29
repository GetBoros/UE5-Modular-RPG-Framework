//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Button_Response.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Response_Clicked, int32, index);
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UMaterialInstanceDynamic;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Response : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct();
    
    void Init(const FPlayer_Response &data, const int32 index);  // Init button with data
    
    UPROPERTY(BlueprintAssignable) FOn_Response_Clicked On_Response_Clicked_Delegate;  // Делегат, на который подпишется родитель (Диалог), чтобы узнать о клике
	
private:
    int32 Response_Index = -1;

    void Button_Update_Visuals(EDialogue_Response_Category dialogue_response_category);  // Change button color based on Response category
    FLinearColor Get_Color_By_Category(EDialogue_Response_Category dialogue_response_category) const;

    UFUNCTION(meta = (AllowPrivateAccess = "true") ) void Handle_Button_Clicked();
    
    UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget) ) TObjectPtr<UButton> Button_Click;
    UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget) ) TObjectPtr<UTextBlock> TB_Response;
    UPROPERTY(meta = (AllowPrivateAccess = "true") ) TObjectPtr<UMaterialInstanceDynamic> MID_Button;
};
//------------------------------------------------------------------------------------------------------------
