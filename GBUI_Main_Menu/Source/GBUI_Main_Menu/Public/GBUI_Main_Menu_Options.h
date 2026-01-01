//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GameplayTagContainer.h>
#include <GBUI_Main_Menu_Options.generated.h>
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGBUI_Menu_Button_Info
{
    GENERATED_BODY()

    // !!! TEMP Experimental
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Button_Text;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTag Button_Tag;
};
//------------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UGBUI_Main_Menu_Options : public UUserWidget
{
	GENERATED_BODY()
public:

    //UPROPERTY(EditDefaultsOnly) TArray<FGBUI_Menu_Button_Info> Buttons_Config;
    //UPROPERTY(EditDefaultsOnly) TSubclassOf<UGBUI_Main_Menu_Button> Button_Class;

};
//------------------------------------------------------------------------------------------------------------
