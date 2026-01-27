//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Data/TLG_Types.h>
#include <Blueprint/UserWidget.h>

#include <TLG_Widget_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Widget_Dialogue;
class UTLG_Widget_Controller;
class UTLG_Widget_Button_Navigation;
class UGBC_Attribute_Info;
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

    void Set_Image_Background_Texture(UTexture2D *image_background_texture) const;
	void Update_Navigation_Buttons(const TArray<FTLG_Location_Exit> &tlg_location_exits);

    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Sanity(float sanity_curr, float sanity_max);
    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Dominance(float dominance_curr);
    UFUNCTION(BlueprintImplementableEvent) void On_Update_Enemy_Portrait(UTexture2D *texture);

    UFUNCTION(BlueprintNativeEvent) void On_Updated_Temp(float sanity_curr, float sanity_max);  // !!! TEMP Example

private:
    void Init_Widget_Controller();
    void Spawn_Floating_Text(const float delta, const FText &name_text);

    UFUNCTION() void On_Changed_Callback_Sanity(float new_value, float delta);
    UFUNCTION() void On_Changed_Callback_Dominance(float new_value, float delta);

    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Background;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Events;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Navigation;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Dialogue> TLG_Widget_Dialogue;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> Floating_Text_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Controller> TLG_Widget_Controller_Class;
    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UTLG_Widget_Button_Navigation> TLG_Widget_Button_Navigation_Class;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UGBC_Attribute_Info> GBC_Attribute_Info;
    UPROPERTY(Transient, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Widget_Controller> TLG_Widget_Controller;

};
//------------------------------------------------------------------------------------------------------------
