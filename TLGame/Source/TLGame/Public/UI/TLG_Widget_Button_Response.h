//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLTypes.h>
#include <Blueprint/UserWidget.h>
#include <TLG_Widget_Button_Response.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Response_Clicked, int32, index);
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Button_Response : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct();
    
    int32 Response_Index = -1;
    
    UFUNCTION(BlueprintCallable) void Init(const FPlayer_Response &data, int32 index);  // Init button with data
    UFUNCTION() void Handle_Button_Clicked();
    
    UPROPERTY(BlueprintAssignable) FOn_Response_Clicked On_Response_Clicked_Delegate;  // Делегат, на который подпишется родитель (Диалог), чтобы узнать о клике
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UButton> Button_Click;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_Response;
	
};
//------------------------------------------------------------------------------------------------------------
