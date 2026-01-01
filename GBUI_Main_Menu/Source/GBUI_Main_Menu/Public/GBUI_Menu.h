//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GameplayTagContainer.h>

#include <GBUI_Menu.generated.h>
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGBUI_Menu_Button_Info
{
    GENERATED_BODY()

    // !!! TEMP Experimental
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Button_Text;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Button_Tag; // Чтобы понять, на что нажали (например, Menu.Action.NewGame)
};
//------------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UGBUI_Main_Menu_Button;
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class GBUI_MAIN_MENU_API UGBUI_Main_Menu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct();
    virtual void NativeConstruct();

    // !!! TEMP Experimental
    UPROPERTY(meta = (BindWidget) ) UVerticalBox *VB_Button_Container;
    UPROPERTY(EditDefaultsOnly) TArray<FGBUI_Menu_Button_Info> Buttons_Config;
    UPROPERTY(EditDefaultsOnly) TSubclassOf<UGBUI_Main_Menu_Button> Button_Class;

};
//------------------------------------------------------------------------------------------------------------
