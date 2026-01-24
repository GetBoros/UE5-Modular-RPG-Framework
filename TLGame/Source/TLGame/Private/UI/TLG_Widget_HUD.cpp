//------------------------------------------------------------------------------------------------------------
#include <UI/TLG_Widget_HUD.h>
#include <UI/TLG_Widget_Dialogue.h>
#include <UI/TLG_Widget_Controller.h>
#include <UI/TLG_Widget_Floating_Text.h>
#include <System/TLG_Player_State.h>
#include <Abilities/TLG_Attribute_Set.h>

#include <AbilitySystemComponent.h>
#include <Components/Image.h>
#include <Components/VerticalBox.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_Widget_HUD
void UTLG_Widget_HUD::NativeConstruct()
{
    Init();  // For single it`s oke here
    Init_Widget_Controller();

    ensureMsgf(Attribute_Set, TEXT("Init_GAS_Attributes can`t get Attribute_Set") );
    ensureMsgf(Ability_System_Component, TEXT("Init_GAS_Attributes can`t get Ability_System_Component") );
    ensureMsgf(Floating_Text_Class, TEXT("Floating Text Class not setting up") );
    ensureMsgf(Widget_Controller_Class, TEXT("Is Empty") );

    Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Init()
{
    APlayerController *player_controller;
    ATLG_Player_State *player_state;

	// 1.0. Get Player State and its Ability System Component + Attribute Set
    player_controller = GetOwningPlayer();
    if (player_controller == 0)
        return;

    player_state = player_controller->GetPlayerState<ATLG_Player_State>();
    if (player_state == 0)
        return;

    Ability_System_Component = player_state->GetAbilitySystemComponent();
    Attribute_Set = player_state->Get_Attribute_Set();

    if (Ability_System_Component == 0 || Attribute_Set == 0)
        return;
    
	// 1.1. Bind delegates for attribute changes
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetSanityAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Sanity);
    Ability_System_Component->GetGameplayAttributeValueChangeDelegate(Attribute_Set->GetDominanceAttribute() ).AddUObject(this, &UTLG_Widget_HUD::Handle_Changed_Dominance);

    // 2.0. Call BP Events to first init
    Prev_Sanity = Attribute_Set->GetSanity();
	Dominance_Prev = Attribute_Set->GetDominance();

    On_Updated_Sanity(Attribute_Set->GetSanity(), Attribute_Set->GetSanity_Max() );
    On_Updated_Dominance(Attribute_Set->GetDominance() );
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Init_Widget_Controller()
{
    if (TLG_Widget_Controller != 0)
        return;

    APlayerController *pc = GetOwningPlayer();
    if (pc == 0)
        return;

    ATLG_Player_State *ps = pc->GetPlayerState<ATLG_Player_State>();
    if (ps == 0)
        return;

    UAbilitySystemComponent *asc = ps->GetAbilitySystemComponent();
    UTLG_Attribute_Set *as = ps->Get_Attribute_Set();

    if (asc == 0 || as == 0)
        return;

    // 1. Создаем Контроллер
    if (Widget_Controller_Class != 0)
    {
        TLG_Widget_Controller = NewObject<UTLG_Widget_Controller>(this, Widget_Controller_Class);
        
        // 2. Заполняем структуру параметров (из твоего Core)
        FController_Widget_Params_Temp params;
        params.Player_Controller = pc;
        params.Player_State = ps;
        params.Ability_System_Component = asc;
        params.Attribute_Set = as; // Тут может потребоваться Cast, если в структуре UAttributeSet*
        
        TLG_Widget_Controller->Init(params);

        // 3. Подписываемся на делегаты (Связываем Controller -> View)
        TLG_Widget_Controller->On_Changed_Sanity.AddDynamic(this, &UTLG_Widget_HUD::On_Sanity_Changed_Callback);
        TLG_Widget_Controller->On_Changed_Dominance.AddDynamic(this, &UTLG_Widget_HUD::On_Dominance_Changed_Callback);

        // 4. Запускаем (Controller -> Model)
        TLG_Widget_Controller->Bind_Callbacks_To_Dependencies();
        TLG_Widget_Controller->Broadcast_Initial_Values();
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Show_Node(const FDialogue_Node &node_data) const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Visible);
    TLG_Widget_Dialogue->Setup_Dialogue_Node(node_data);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Dialogue_Hide() const
{
    TLG_Widget_Dialogue->SetVisibility(ESlateVisibility::Hidden);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Sanity_Changed_Callback(float new_value, float delta)
{
    On_Updated_Sanity(new_value, 100.0f); // Макс можно тоже прокинуть через контроллер, если нужно

    if (!FMath::IsNearlyZero(delta))
    {
        Spawn_Floating_Text(delta, FText::FromString("Sanity"));
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Dominance_Changed_Callback(float new_value, float delta)
{
    On_Updated_Dominance(new_value);

    if (!FMath::IsNearlyZero(delta))
    {
        Spawn_Floating_Text(delta, FText::FromString("Dominance"));
    }
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::On_Updated_Temp_Implementation(float sanity_curr, float sanity_max)
{
    // !!! TEMP
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Set_Image_Background_Texture(UTexture2D *image_background_texture) const
{
    Image_Background->SetBrushFromTexture(image_background_texture);
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Changed_Sanity(const FOnAttributeChangeData &data)
{
    float sanity_curr = data.NewValue;
    float sanity_max = 100.0f;
    float delta = 0.0f;

    if (Attribute_Set != 0)  // Problev with dominance
        sanity_max = Attribute_Set->GetSanity_Max();

    On_Updated_Sanity(sanity_curr, sanity_max);

    if (Prev_Sanity < 0.0f)
    {
        Prev_Sanity = sanity_curr;
        return;
    }

    delta = sanity_curr - Prev_Sanity;
	if (FMath::IsNearlyZero(delta) != true)  // if has change spawn floating text
        Spawn_Floating_Text(delta, FText::FromString("Sanity") );

    Prev_Sanity = sanity_curr;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Handle_Changed_Dominance(const FOnAttributeChangeData &data)
{
    float current = data.NewValue;
	float delta = 0.0f;

    On_Updated_Dominance(data.NewValue);

    if (Dominance_Prev < 0.0f)
    {
        Dominance_Prev = current;
        return;
    }

    delta = current - Dominance_Prev;

    if (FMath::IsNearlyZero(delta) != true)
        Spawn_Floating_Text(delta, FText::FromString("Dominance") );

    Dominance_Prev = current;
}
//------------------------------------------------------------------------------------------------------------
void UTLG_Widget_HUD::Spawn_Floating_Text(float delta, const FText &name_text)
{
    UUserWidget *widget;
    UTLG_Widget_Floating_Text *float_widget;

    if (VB_Events == 0 || Floating_Text_Class == 0)
        return;

    widget = CreateWidget<UUserWidget>(this, Floating_Text_Class);
    float_widget = Cast<UTLG_Widget_Floating_Text>(widget);
    if (float_widget == 0)
        return;

    FString sign = (delta > 0) ? TEXT("+") : TEXT("");
    FText final_text = FText::FromString(FString::Printf(TEXT("%s%d %s"), *sign, FMath::RoundToInt(delta), *name_text.ToString() ) );
    FLinearColor color = (delta > 0) ? FLinearColor::Green : FLinearColor::Red;  // !!! TEMP can change if dominance to swap color
    
    float_widget->Setup_Visuals(final_text, color);
    
    VB_Events->AddChild(float_widget);
}
//------------------------------------------------------------------------------------------------------------
