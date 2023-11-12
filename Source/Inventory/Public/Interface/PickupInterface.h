// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

class AItem;

UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY_API IPickupInterface
{
	GENERATED_BODY()

public:

	virtual void AddMoney(const int32 InAmount) = 0;
	virtual void SetOverlappingItem(AItem* Item) = 0;
	virtual AItem* GetOverlappingItem() = 0;
	virtual void AddToInventory() = 0;
	
};
