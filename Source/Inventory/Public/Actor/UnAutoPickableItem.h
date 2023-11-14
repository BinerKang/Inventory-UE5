// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item.h"
#include "UnAutoPickableItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API AUnAutoPickableItem : public AItem
{
	GENERATED_BODY()

public:

	void InitialItem(const EPickableItemName InEItemID, UPickableItemDataAsset* ItemDataAsset);
	
protected:
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float SimulationSeconds = 5.f;
	
private:
	FTimerHandle DisableTimer;
	
	void DisablePhysicalSimulation();
};
