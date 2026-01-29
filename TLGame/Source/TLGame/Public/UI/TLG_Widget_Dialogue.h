//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>
#include <GBUIC_User_Widget.h>

#include <TLG_Widget_Dialogue.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Typewriter_Text;
class UTLG_Widget_Button_Response;
class UTextBlock;
class UVerticalBox;
class URetainerBox;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Dialogue : public UGBUIC_User_Widget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct();

    void Setup_Dialogue_Node(const FDialogue_Node &dialogue_node);  // Main func call her to show primary dialogue
    
    UFUNCTION(BlueprintImplementableEvent) void On_Response_Selected(const FPlayer_Response &selected_response);  // Event Player resonse | can add sound or else
    
private:
    void Set_Text_Distortion(const float value) const;
    void Set_Text_Tint(const FLinearColor &linear_color) const;

    FDialogue_Node Dialogue_Node_Current;  // Current data need to know what we choose

    UFUNCTION() void Handle_Response_Clicked(int32 response_index);

    UPROPERTY() TObjectPtr<UMaterialInstanceDynamic> MID_Effect;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Typewriter_Text> TLG_Typewriter_Text_NPC_Line;

    UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<UTextBlock> TB_Speaker_Name;
    UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<URetainerBox> RB_NPC_Line_Effect;
    UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true") ) TObjectPtr<UVerticalBox> VB_TLG_Widget_Button_Response_Container;  // Used for spawn button or widgets

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Response> TLG_Widget_Button_Response_Class;

};
//------------------------------------------------------------------------------------------------------------
