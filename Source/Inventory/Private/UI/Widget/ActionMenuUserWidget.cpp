// Copyright Jack Kong.


#include "UI/Widget/ActionMenuUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/WidgetController/InvWidgetController.h"

void UActionMenuUserWidget::SetActionNames(EPickableItemName InEItemID, UInvWidgetController* InInvWC, const FText& UseName, const FText& DropName)
{
	UseText->SetText(UseName);
	DropText->SetText(DropName);
	EItemID = InEItemID;
	InvWC = InInvWC;
	
}

void UActionMenuUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	OnActionMenuMouseLeaveDelegate.Broadcast();
	SetVisibility(ESlateVisibility::Hidden);
}

void UActionMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CancelButton->OnClicked.AddDynamic(this, &ThisClass::HideSelf);
	UseButton->OnClicked.AddDynamic(this, &ThisClass::UseItem);
	DropButton->OnClicked.AddDynamic(this, &ThisClass::DropItem);
}

void UActionMenuUserWidget::HideSelf()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UActionMenuUserWidget::UseItem()
{
	InvWC->ServerUseItem(EItemID);
	SetVisibility(ESlateVisibility::Hidden);
}

void UActionMenuUserWidget::DropItem()
{
	InvWC->ServerDropItem(EItemID);
	SetVisibility(ESlateVisibility::Hidden);
}
