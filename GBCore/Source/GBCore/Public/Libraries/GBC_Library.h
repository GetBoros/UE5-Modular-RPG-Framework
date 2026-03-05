//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Kismet/BlueprintFunctionLibrary.h>

#include <GBC_Library.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBC_Library : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Converts minutes into a readable string (e.g., "2h", "3d", "45min").
     * Best used for displaying Action Costs.
     */
    UFUNCTION(BlueprintPure) static FText Format_Time_From_Minutes(int32 minutes);
};
//------------------------------------------------------------------------------------------------------------
