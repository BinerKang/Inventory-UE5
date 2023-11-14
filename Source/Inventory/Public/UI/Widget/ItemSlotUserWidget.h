// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotUserWidget.generated.h"

struct FOwnedItemInfo;
struct FPickableItemInfo;
class UImage;
enum class EPickableItemName : uint8;
class UTextBlock;
class UButton;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemButtonEventSinature, EPickableItemName);
/**
 * 
 */
UCLASS()
class INVENTORY_API UItemSlotUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemInfo(const FPickableItemInfo& ItemInfo, const FOwnedItemInfo& OwnedItemInfo);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> HoverBorderImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> EquippedBgImage;
	
	FOnItemButtonEventSinature OnItemButtonHoveredDelegate;
	FOnItemButtonEventSinature OnItemButtonUnHoveredDelegate;
	FOnItemButtonEventSinature OnItemButtonPressedDelegate;
private:
	
	EPickableItemName EItemID;
	
	UFUNCTION()
	void OnItemButtonHovered();

	UFUNCTION()
	void OnItemButtonUnHovered();

	UFUNCTION()
	void OnItemButtonPressed();
};
