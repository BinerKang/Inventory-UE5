// Copyright Jack Kong.


#include "UI/Widget/InventoryUserWidget.h"
#include "UI/Widget/ProgressBarUserWidget.h"
#include "UI/WidgetController/InvWidgetController.h"
#include "Components/TextBlock.h"
#include "Framework/InvPlayerController.h"
#include "Kismet/KismetTextLibrary.h"
#include "UI/Widget/ContentSwitcherUserWidget.h"

void UInventoryUserWidget::SetInvWidgetController(UInvWidgetController* InWidgetController)
{
	SetIsFocusable(true);
	
	InvWidgetController = InWidgetController;

	InvWidgetController->OnMoneyChangedDelegate.AddLambda(
		[this](const int32 NewMoney)
		{
			TextMoney->SetText(UKismetTextLibrary::Conv_IntToText(NewMoney));
		}
	);

	InvWidgetController->OnHealthChangedDelegate.AddLambda(
	[this](const float NewHealth)
		{
			HealthBar->SetValue(NewHealth);
		}
	);

	InvWidgetController->OnMaxHealthChangedDelegate.AddLambda(
	[this](const float NewMaxHealth)
		{
			HealthBar->SetMaxValue(NewMaxHealth);
		}
	);

	ContainerSwitcher->SetInvWidgetController(InvWidgetController);
	InvWidgetController->OnInventoryChangedDelegate.AddLambda(
		[this](const TArray<FOwnedItemCategory>& NewAllItems)
		{
			ContainerSwitcher->UpdateInventoryContainer(NewAllItems);
		}
	);
	
}

FReply UInventoryUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (Reply.IsEventHandled()) return Reply;

	if (InKeyEvent.GetKey() == EKeys::I || InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (AInvPlayerController* PC = Cast<AInvPlayerController>(InvWidgetController->PlayerController))
		{
			PC->ToggleInventoryWidget();
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

