// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/UserWidgetBase.h"
#include "InventoryUserWidget.generated.h"

class UInvWidgetController;
class UContentSwitcherUserWidget;
class UProgressBarUserWidget;
class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInventoryUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void SetInvWidgetController(UInvWidgetController* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInvWidgetController> InvWidgetController;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextMoney;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBarUserWidget> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UContentSwitcherUserWidget> ContainerSwitcher;

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
