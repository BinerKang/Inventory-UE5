// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Framework/MainPlayerState.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "InvWidgetController.generated.h"

class UPickableItemDataAsset;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnIntInfoChangedSignature, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFloatInfoChangedSignature, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnArrayInfoChangedSignature, const TArray<FOwnedItemCategory>&);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INVENTORY_API UInvWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindDelegates();

	UFUNCTION(BlueprintCallable)
	void BroadcastDefaultValues();
	
	FOnIntInfoChangedSignature OnMoneyChangedDelegate;
	
	FOnFloatInfoChangedSignature OnHealthChangedDelegate;
	
	FOnFloatInfoChangedSignature OnMaxHealthChangedDelegate;
	
	FOnArrayInfoChangedSignature OnInventoryChangedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UPickableItemDataAsset> PickableItemDataAsset;

	UFUNCTION(Server, Reliable)
	void ServerUseItem(EPickableItemName EItemID);

	UFUNCTION(Server, Reliable)
	void ServerDropItem(EPickableItemName EItemID);
};
