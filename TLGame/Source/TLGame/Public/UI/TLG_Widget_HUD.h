//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Blueprint/UserWidget.h>
#include <GameplayEffectTypes.h>
#include <Data/TLG_Types.h>

#include <TLG_Widget_HUD.generated.h>
//------------------------------------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UTLG_Attribute_Set;
class UTLG_Widget_Dialogue;
class UImage;
class UVerticalBox;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_HUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();

    void Dialogue_Show_Node(const FDialogue_Node &node_data) const;
    void Dialogue_Hide() const;

    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Sanity(float sanity_curr, float sanity_max);
    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Dominance(float dominance_curr);

    UFUNCTION(BlueprintNativeEvent) void On_Updated_Temp(float sanity_curr, float sanity_max);

private:
    void Init();

    void Set_Image_Background_Texture(UTexture2D *image_background_texture) const;

    void Handle_Changed_Sanity(const FOnAttributeChangeData &data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &data);
    
    void Spawn_Text_Delta(float delta, const FText &name_text);

    float Prev_Sanity = -1.0f;
    float Dominance_Prev = -1.0f;

    UPROPERTY() TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY() TObjectPtr<UTLG_Attribute_Set> Attribute_Set;
    
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Dialogue> TLG_Widget_Dialogue;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Background;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UVerticalBox> VB_Events;

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true") ) TSubclassOf<UUserWidget> Floating_Text_Class;
};
//------------------------------------------------------------------------------------------------------------
