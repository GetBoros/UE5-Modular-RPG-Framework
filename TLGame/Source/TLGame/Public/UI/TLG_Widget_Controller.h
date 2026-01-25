//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GBUIC_Widget_Controller.h>

#include <TLG_Widget_Controller.generated.h>
//------------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOn_Attribute_Changed_Signature, float, new_value, float, delta);
//------------------------------------------------------------------------------------------------------------
class UTLG_Attribute_Set;
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API UTLG_Widget_Controller : public UGBUIC_Widget_Controller_Temp
{
    GENERATED_BODY()

public:
    virtual void Broadcast_Initial_Values() override;
    virtual void Bind_Callbacks_To_Dependencies() override;

    void Handle_Changed_Sanity(const FOnAttributeChangeData &data);
    void Handle_Changed_Dominance(const FOnAttributeChangeData &data);

    UTLG_Attribute_Set *Get_TLG_Attribute_Set() const;

    float Prev_Sanity = -1.0f;
    float Prev_Dominance = -1.0f;
    
    UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Signature On_Changed_Sanity;
    UPROPERTY(BlueprintAssignable) FOn_Attribute_Changed_Signature On_Changed_Dominance;
};
//------------------------------------------------------------------------------------------------------------
