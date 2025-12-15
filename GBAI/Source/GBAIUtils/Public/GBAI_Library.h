//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Kismet/BlueprintFunctionLibrary.h>
#include <GBAI_Library.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAIUTILS_API UGBAI_Library : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GBAI|Utils") static void Log_GB_Event(const FString &msg);
	UFUNCTION(BlueprintCallable, Category = "GBAI|Utils") static bool Is_Actor_Valid(const AActor *actor_to_check);

};
//------------------------------------------------------------------------------------------------------------
