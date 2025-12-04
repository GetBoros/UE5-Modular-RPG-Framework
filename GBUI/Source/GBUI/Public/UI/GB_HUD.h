//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameFramework/HUD.h"
#include "GB_HUD.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_API AGB_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UUserWidget> Player_HUD_Widget_Class;
    UPROPERTY() UUserWidget *Player_HUD_Widget;
};
//------------------------------------------------------------------------------------------------------------
