//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Dialogue;
class UTLG_Widget_Portrait;
class UTLG_Widget_Controller;
class UTLG_Widget_Button_Navigation;
class UTLG_Widget_Text_Floating;
class UGBC_Attribute_Info;
class UTextBlock;
class UImage;
class UVerticalBox;
struct FTLG_Location_Exit;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_HUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();

    void Dialogue_Node_Show(const FDialogue_Node &node_data);
    void Dialogue_Hide() const;

    void Set_Image_Texture_Background(UTexture2D* image_background_texture) const;
    void Set_Image_Texture_Portrait(UTexture2D *image_portrait_texture);
	void Update_Navigation_Buttons(const TArray<FTLG_Location_Exit> &tlg_location_exits);

    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Sanity(float sanity_curr, float sanity_max);
    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Dominance(float dominance_curr);

    UFUNCTION(BlueprintNativeEvent) void On_Updated_Temp(float sanity_curr, float sanity_max);  // !!! TEMP Example

private:
    void Init_Widget_Controller();
    void Spawn_Text_Floating(const float delta, const FText &name_text);  // Spawn in VB_Text_Floating_Events container

    UFUNCTION() void On_Changed_Callback_Sanity(float new_value, float delta);
    UFUNCTION() void On_Changed_Callback_Dominance(float new_value, float delta);
    UFUNCTION() void On_Changed_Callback_Time_Game(int32 hours, int32 minutes);

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Background;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Text_Floating_Events;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Button_Navigation;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Dialogue> TLG_Widget_Dialogue;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Portrait> TLG_Widget_Portrait_Hero;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Portrait> TLG_Widget_Portrait_Enemy;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTextBlock> Text_Clock;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Controller> TLG_Widget_Controller_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Text_Floating> TLG_Widget_Text_Floating;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Navigation> TLG_Widget_Button_Navigation_Class;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBC_Attribute_Info> GBC_Attribute_Info;
    UPROPERTY(Transient, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Widget_Controller> TLG_Widget_Controller;

};
//------------------------------------------------------------------------------------------------------------
