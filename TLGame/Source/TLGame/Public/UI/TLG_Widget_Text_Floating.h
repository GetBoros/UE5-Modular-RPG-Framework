//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_Text_Floating.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Text_Floating : public UUserWidget
{
    GENERATED_BODY()

public:
    void Setup_Visuals(const FText &text, const FLinearColor &color);

    UFUNCTION(BlueprintImplementableEvent) void Play_Intro_Animation();
    
private:
    UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<UTextBlock> TB_Floating;

};
//------------------------------------------------------------------------------------------------------------
