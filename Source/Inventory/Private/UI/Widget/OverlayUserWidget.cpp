// Copyright Jack Kong.


#include "UI/Widget/OverlayUserWidget.h"

#include "UI/Widget/ProgressBarUserWidget.h"
#include "UI/Widget/ItemDetailUserWidget.h"
#include "UI/WidgetController/InvWidgetController.h"

void UOverlayUserWidget::SetPickupHintVisibility(bool bIsShow, EPickableItemName EItemID) const
{
	if (bIsShow)
	{
		PickupHint->SetVisibility(ESlateVisibility::Visible);
		ItemDetail->SetItemDetail(EItemID, InvWidgetController);
		ItemDetail->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		PickupHint->SetVisibility(ESlateVisibility::Hidden);
		ItemDetail->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UOverlayUserWidget::SetInvWidgetController(UInvWidgetController* InWidgetController)
{
	InvWidgetController = InWidgetController;

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

}
