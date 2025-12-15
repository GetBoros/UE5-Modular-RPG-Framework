//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "UObject/Interface.h"
#include "GBC_Health_Owner_Interface.generated.h"
//------------------------------------------------------------------------------------------------------------

UINTERFACE(MinimalAPI) class UGBC_Health_Owner_Interface : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class GBCORE_API IGBC_Health_Owner_Interface
{
	GENERATED_BODY()

public:
	// Пример функции, которую мог бы использовать компонент регенерации
	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	// UHealthComponent* GetHealthComponent();
};
//------------------------------------------------------------------------------------------------------------
