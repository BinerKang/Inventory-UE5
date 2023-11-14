// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Inventory/Inventory.h"
#include "PickableItemDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FPickableItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPickableItemCategory Category = EPickableItemCategory::EPIC_Eatable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxStack = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Power = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh;
	
};

USTRUCT()
struct FItemCategoryInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly)
	FText Category = FText();

	UPROPERTY(EditDefaultsOnly)
	FText UseActionName = FText();

	UPROPERTY(EditDefaultsOnly)
	FText DropActionName = FText();
};

/**
 * 
 */
UCLASS()
class INVENTORY_API UPickableItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<EPickableItemName, FPickableItemInfo> ItemInfos;

	UPROPERTY(EditDefaultsOnly)
	TMap<EPickableItemCategory, FItemCategoryInfo> CategoryInfos;
	
	UFUNCTION(BlueprintCallable)
	FPickableItemInfo GetItemInfoByName(EPickableItemName Name) const;
	
	FItemCategoryInfo GetCategoryInfoByECategory(EPickableItemCategory Category) const;

	FItemCategoryInfo GetCategoryInfoByEItemID(EPickableItemName EItemID) const;
};
