//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLTypes.h>
#include <GBUIC_User_Widget.h>
#include <TLG_Widget_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UVerticalBox;
class UButton;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Dialogue : public UGBUIC_User_Widget
{
	GENERATED_BODY()

public:
    FDialogue_Node Current_Node;  // Current data need to know what we choose
    
    UFUNCTION(BlueprintImplementableEvent) void On_Response_Selected(const FPlayer_Response &selected_response);  // Event Player resonse | can add sound or else
    UFUNCTION(BlueprintCallable) void Setup_Dialogue_Node(const FDialogue_Node &node_data);  // Main func call her to show primary dialogue
    UFUNCTION() void Handle_Response_Clicked(int32 response_index);
    
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_NPC_Line;
    UPROPERTY(meta = (BindWidget)) TObjectPtr<UVerticalBox> Buttons_Response_Container;  // Used for spawn button or widgets
    UPROPERTY(EditDefaultsOnly, Category = "ToxicLove|UI") TSubclassOf<UUserWidget> Button_Response_Class;  // Widget Button to spawn in container

};
//------------------------------------------------------------------------------------------------------------
