// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/UserWidgetBase.h"
#include "OverlayUserWidget.generated.h"

class UItemDetailUserWidget;
class UInvWidgetController;
class UProgressBarUserWidget;
/**
 * 
 */
UCLASS()
class INVENTORY_API UOverlayUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void SetPickupHintVisibility(bool bIsShow, EPickableItemName EItemID) const;
	
	void SetInvWidgetController(UInvWidgetController* InWidgetController);
	
protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInvWidgetController> InvWidgetController;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UUserWidget> PickupHint;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBarUserWidget> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UItemDetailUserWidget> ItemDetail;
};
