// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MoneyDataAsset.generated.h"

UENUM(BlueprintType)
enum class EMoneyType : uint8
{
	EMT_Green UMETA(DisplayName = "Green"),
	EMT_Blue UMETA(DisplayName = "Blue"),
	EMT_Red UMETA(DisplayName = "Red"),
	EMT_Silver UMETA(DisplayName = "Silver"),
	EMT_Gold UMETA(DisplayName = "Gold")
};

USTRUCT(BlueprintType)
struct FMoneyInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> MoneyMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MoneyAmount = 0;
};

/**
 * 
 */
UCLASS()
class INVENTORY_API UMoneyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<EMoneyType, FMoneyInfo> MoneyInfos;

	UFUNCTION(BlueprintCallable)
	FMoneyInfo GetMoneyInfoByType(EMoneyType Type) const;
};
