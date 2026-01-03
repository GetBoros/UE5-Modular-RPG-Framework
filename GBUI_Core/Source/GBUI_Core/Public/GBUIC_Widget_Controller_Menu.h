//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GBUI_Widget_Controller.h"
#include "GBUIC_Widget_Controller_Menu.generated.h"
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Menu_State_Changed_Signature, FGameplayTag, new_state_tag);
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBUI_CORE_API UGBUIC_Widget_Controller_Menu : public UGBUI_Widget_Controller
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GBUI | Menu") void Set_Menu_State(FGameplayTag new_state);  // Функция, которую вызовет кнопка в UI: "Я хочу перейти в настройки"
    
    UPROPERTY(BlueprintAssignable, Category = "GBUI | Events") FOn_Menu_State_Changed_Signature On_Menu_State_Changed;  // Ивент, который скажет Виджету: "Переключись!"

protected:
    UPROPERTY(BlueprintReadOnly, Category = "GBUI | State") FGameplayTag Current_State;  // Текущее состояние (чтобы знать, куда возвращаться, если нужно)
	
};
//------------------------------------------------------------------------------------------------------------
