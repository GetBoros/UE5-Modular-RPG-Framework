//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "UObject/Interface.h"
#include "GBC_AI_Target_Interface.generated.h"
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI) class UGBC_AI_Target_Interface : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class GBCORE_API IGBC_AI_Target_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI|Target") FVector Get_Target_Location();
};
//------------------------------------------------------------------------------------------------------------
