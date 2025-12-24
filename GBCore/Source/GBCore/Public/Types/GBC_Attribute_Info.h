//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GameplayTagContainer.h>
#include <AttributeSet.h>
#include <GBC_Attribute_Info.generated.h>
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGBC_Attribute_Info_Item
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayTag Attribute_Tag = FGameplayTag();  // Find key (example, Attributes.Vitality.Stamina)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FGameplayAttribute Attribute_To_Bind;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FText Attribute_Name = FText();  // Name for UI example Stamina
};
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBC_Attribute_Info : public UDataAsset
{
    GENERATED_BODY()

public:
    FGBC_Attribute_Info_Item Find_Attribute_Info_By_Tag(const FGameplayTag &tag, bool b_log_not_found = false) const;  // helper to find by tag

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config") TArray<FGBC_Attribute_Info_Item> Attribute_Information;
};
//------------------------------------------------------------------------------------------------------------