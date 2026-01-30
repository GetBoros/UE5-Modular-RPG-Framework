//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/Character.h>
#include <Data/TLG_Data_Enemy.h>

#include <TLG_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Enemy : public ACharacter  // !!! TEMP Delete
{
    GENERATED_BODY()

public:
    ATLG_Enemy();

    UFUNCTION(BlueprintCallable) UTLG_Data_Enemy *Get_Enemy_Data() const;  // !!! Example

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Data_Enemy> Enemy_Data;  // From BP can put example DA_Hysteric

};
//------------------------------------------------------------------------------------------------------------
