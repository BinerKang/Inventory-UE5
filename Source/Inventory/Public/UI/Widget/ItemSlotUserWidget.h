// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotUserWidget.generated.h"

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
	void SetItemInfo(UTexture2D* Icon, int32 Quantity, EPickableItemName InItemId);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	FOnItemButtonEventSinature OnItemButtonHoveredDelegate;
	FOnItemButtonEventSinature OnItemButtonUnHoveredDelegate;
private:
	
	EPickableItemName EItemID;
	
	UFUNCTION()
	void OnItemButtonHovered();

	UFUNCTION()
	void OnItemButtonUnHovered();
};
