// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PickableItemDataAsset.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

USTRUCT(BlueprintType)
struct FOwnedItemInfo
{
	GENERATED_BODY()

	FOwnedItemInfo() {}
	FOwnedItemInfo(const EPickableItemName InItemID, const int32 InQuantity)
	{
		EItemID = InItemID;
		Quantity = InQuantity;
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPickableItemName EItemID = EPickableItemName::EPIN_Apple;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsEquipped = false;
};

USTRUCT(BlueprintType)
struct FOwnedItemCategory
{
	GENERATED_BODY()
	FOwnedItemCategory(){}

	FOwnedItemCategory(EPickableItemCategory InCategory)
	{
		Category = InCategory;
	}
	
	UPROPERTY(BlueprintReadOnly)
	EPickableItemCategory Category = EPickableItemCategory::EPIC_Eatable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FOwnedItemInfo> ItemInfos;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayStateChangedIntSignature, const int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FPlayStateChangedFloatSignature, const float)
DECLARE_MULTICAST_DELEGATE_OneParam(FPlayStateChangedArraySignature, const TArray<FOwnedItemCategory>&)
/**
 * 
 */
UCLASS()
class INVENTORY_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMainPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FPlayStateChangedIntSignature OnMoneyChangedDelegate;
	FPlayStateChangedFloatSignature OnHealthChangedDelegate;
	FPlayStateChangedFloatSignature OnMaxHealthChangedDelegate;
	FPlayStateChangedArraySignature OnInventoryChangedDelegate;

	FORCEINLINE int32 GetMoney() const { return Money; }
	void AddToMoney(const int32 InAmount);

	FORCEINLINE float GetHealth() const { return Health; }
	void AddToHealth(const float InValue);

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	void AddToMaxHealth(const float InValue);

	FORCEINLINE TArray<FOwnedItemCategory>& GetAllItems() { return AllItems; }
	void AddToOwnedItems(const FPickableItemInfo& Info, const EPickableItemName EItemID);

	/* Eat or Drop Item*/
	void ConsumeItem(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo);

	void UpdateEquipState(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo);
	
	void UseItem(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo);
	void DropItem(EPickableItemName EItemID, UPickableItemDataAsset* ItemDataAsset);
	
protected:

	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_Money, Category="Custom")
	int32 Money = 0;

	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_Health, Category="Custom")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_MaxHealth, Category="Custom")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing=OnRep_AllItems, Category="Custom")
	TArray<FOwnedItemCategory> AllItems;
	
	UFUNCTION()
	void OnRep_Money(int32 OldMoney) const;
	
	UFUNCTION()
	void OnRep_Health(float OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(float OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_AllItems(TArray<FOwnedItemCategory> OldItems) const;
	
};
