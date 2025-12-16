//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Engine/DataAsset.h>
#include <GBC_Item_Data.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API UGBC_Item_Data : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(Type, GetFName() ); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay") int32 MaxStackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data") FPrimaryAssetType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data") FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data", meta = (MultiLine = true) ) FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals") TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals") TSoftObjectPtr<UStaticMesh> Static_Mesh;
	
};
//------------------------------------------------------------------------------------------------------------
