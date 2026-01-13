//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameFramework/Character.h>
#include <Data/TLG_Enemy_Data.h>

#include <TLG_Enemy.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class TLGAME_API ATLG_Enemy : public ACharacter
{
    GENERATED_BODY()

public:
    ATLG_Enemy();

    UFUNCTION(BlueprintCallable) UTLG_Enemy_Data *Get_Enemy_Data() const;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") ) TObjectPtr<UTLG_Enemy_Data> Enemy_Data;  // —юда в редакторе положишь DA_Hysteric

};
//------------------------------------------------------------------------------------------------------------
