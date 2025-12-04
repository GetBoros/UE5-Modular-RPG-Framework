//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Types/GB_Types_Health.h"

#include "UObject/Interface.h"
#include "GB_Character_Interface.generated.h"
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI) class UGB_Character_Interface : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class GBCORE_API IGB_Character_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Movement") void Move(const FVector2D &world_direction, float scale_value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Attributes") FGB_Types_Health Get_Types_Health();
};
//------------------------------------------------------------------------------------------------------------
