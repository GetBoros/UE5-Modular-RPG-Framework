//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLTypes.h>
#include <Blueprint/UserWidget.h>
#include <TLG_Dialogue_Widget.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UVerticalBox;
class UButton;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Dialogue_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
    FDialogue_Node Current_Node;  // Текущие данные (чтобы знать, что мы выбрали)
    
    UFUNCTION(BlueprintImplementableEvent) void On_Response_Selected(const FPlayer_Response &selected_response);  // Событие для Блюпринта: "Игрок выбрал ответ, делай что хочешь (анимации, звук)"
    UFUNCTION(BlueprintCallable) void Setup_Dialogue_Node(const FDialogue_Node &node_data);  // Главная функция: Вызвать её, чтобы показать конкретную фразу
    UFUNCTION() void Handle_Response_Clicked(int32 response_index);  // Функция обработки клика (свяжем её с кнопками)
    
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_NPC_Line;  // --- UI Elements (BindWidget) --- // Эти переменные должны совпадать с именами в Designer (WBP)
    UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> Container_Response_Buttons;  // Контейнер, куда будем спавнить кнопки ответов
    UPROPERTY(EditDefaultsOnly, Category = "ToxicLove|UI") TSubclassOf<UUserWidget> Response_Button_Class;  // Класс кнопки, которую будем спавнить (WBP_ResponseButton)

};
//------------------------------------------------------------------------------------------------------------
