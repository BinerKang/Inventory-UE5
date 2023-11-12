// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDetailUserWidget.generated.h"

enum class EPickableItemName : uint8;
class UInvWidgetController;
struct FPickableItemInfo;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UItemDetailUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetItemDetail(EPickableItemName EItemID, UInvWidgetController* InvWC);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextPower;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextDescription;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ImageIcon;

	EPickableItemName EItemID;
};
