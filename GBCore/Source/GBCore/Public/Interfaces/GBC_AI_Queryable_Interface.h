//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <UObject/Interface.h>
#include <GameplayTagContainer.h>
#include <GBC_AI_Queryable_Interface.generated.h>
//------------------------------------------------------------------------------------------------------------
UINTERFACE(Blueprintable) class UGBC_AI_Queryable_Interface : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class GBCORE_API IGBC_AI_Queryable_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI|Query") bool Query_Float_Value_By_Tag(const FGameplayTag &data_tag, float &out_value);
};
//------------------------------------------------------------------------------------------------------------
