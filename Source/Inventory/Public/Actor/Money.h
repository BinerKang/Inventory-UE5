// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item.h"
#include "Money.generated.h"


class UMoneyDataAsset;
enum class EMoneyType : uint8;
/**
 * 
 */
UCLASS()
class INVENTORY_API AMoney : public AItem
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UMoneyDataAsset> MoneyDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	EMoneyType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	int32 Amount;

protected:
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
