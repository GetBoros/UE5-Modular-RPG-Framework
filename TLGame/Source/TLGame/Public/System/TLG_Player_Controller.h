//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/PlayerController.h>
#include <Data/TLG_Types.h>

#include <TLG_Player_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
class ATLG_HUD;
class ATLG_Player_State;
class UAbilitySystemComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Player_Controller : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay();

    void Handle_Player_Decision(const FPlayer_Response &choice);  // Call UI when player press button

private:
    void Apply_Response_Cost(float cost);
    void Apply_Response_Effects(const FGameplayTagContainer &tags);
    void Go_To_Next_Node(FName row_id);  // Функция для загрузки следующего узла

    UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true") ) void Dialogue_Start(const FDialogue_Node &node);
    UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true") ) void Dialogue_Start_Row(FName row_id);  // Запускает диалог по ID строки из таблицы

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UDataTable> Dialogue_Data_Table;

    ATLG_HUD *TLG_HUD;
    ATLG_Player_State *TLG_Player_State;
    UAbilitySystemComponent *Ability_System_Component;
};
//------------------------------------------------------------------------------------------------------------
