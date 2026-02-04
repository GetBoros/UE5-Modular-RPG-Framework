//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <UObject/Interface.h>
#include <GameplayTagContainer.h>

#include <TLG_Interaction_Interface.generated.h>
//------------------------------------------------------------------------------------------------------------
class UTLG_Data_Location;
struct FTLG_Location_Action;
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI) class UTLG_Interaction_Interface : public UInterface
{
    GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class TLGAME_API ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    virtual void Location_Enter(UTLG_Data_Location *tlg_data_location) = 0;
    virtual void Location_Action(const FTLG_Location_Action &tlg_location_action) = 0;
};
//------------------------------------------------------------------------------------------------------------
