// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionMenuUserWidget.generated.h"

class UInvWidgetController;
enum class EPickableItemName : uint8;
DECLARE_MULTICAST_DELEGATE(FOnActionMenuMouseLeaveSignature)

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class INVENTORY_API UActionMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnActionMenuMouseLeaveSignature OnActionMenuMouseLeaveDelegate;

	void SetActionNames(EPickableItemName InEItemID, UInvWidgetController* InInvWC, const FText& UseName, const FText& DropName);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> UseText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> DropButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DropText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;

protected:
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnInitialized() override;

private:
	EPickableItemName EItemID;
	
	TObjectPtr<UInvWidgetController> InvWC;

	UFUNCTION()
	void HideSelf();

	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void DropItem();
};
