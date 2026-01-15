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
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_HUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct();

    void Dialogue_Show_Node(const FDialogue_Node &node_data) const;
    void Dialogue_Hide() const;

    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Sanity(const float sanity_curr, const float sanity_max);
    UFUNCTION(BlueprintImplementableEvent) void On_Updated_Dominance(const float dominance_curr);

private:
    void Init_GAS_Attributes();

    void Set_Image_Background_Texture(UTexture2D *image_background_texture);

    void Handle_Changed_Sanity(const FOnAttributeChangeData &data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &data);

    UPROPERTY() TObjectPtr<UAbilitySystemComponent> Ability_System_Component;
    UPROPERTY() TObjectPtr<UTLG_Attribute_Set> Attribute_Set;
    
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UTLG_Widget_Dialogue> Widget_Dialogue;
    UPROPERTY(meta = (BindWidget) ) TObjectPtr<UImage> Image_Background;
};
//------------------------------------------------------------------------------------------------------------
