// Copyright Jack Kong.


#include "UI/Widget/IconButtonUserWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "UI/WidgetController/InvWidgetController.h"


void UIconButtonUserWidget::SetIndex(const int32 NewIndex, const UInvWidgetController* InvWC)
{
	Index = NewIndex;

	SetBoxSize(NormalSize);

	FButtonStyle& ButtonStyle = const_cast<FButtonStyle&>(Button->GetStyle());
	const FItemCategoryInfo& CategoryInfo = InvWC->PickableItemDataAsset->GetCategoryInfoByECategory(ECategories[NewIndex]);
	ButtonStyle.Normal.SetResourceObject(CategoryInfo.Icon);
	ButtonStyle.Hovered.SetResourceObject(CategoryInfo.Icon);
	ButtonStyle.Disabled.SetResourceObject(CategoryInfo.Icon);
	ButtonStyle.Pressed.SetResourceObject(CategoryInfo.Icon);

	TextCategory->SetText(CategoryInfo.Category);

	if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(Slot))
	{
		HorizontalBoxSlot->SetHorizontalAlignment(HAlign_Center);
		HorizontalBoxSlot->SetVerticalAlignment(VAlign_Center);
	}

	Button->OnClicked.AddDynamic(this, &ThisClass::BroadcastClickEvent);
}

void UIconButtonUserWidget::UpdateChosen(const int32 ChosenIndex) const
{
	if (ChosenIndex == Index) // Chosen
	{
		SetBoxSize(ChosenSize);
		Button->SetIsEnabled(false);
		TextCategory->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else // No Chosen
	{
		SetBoxSize(NormalSize);
		Button->SetIsEnabled(true);
		TextCategory->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UIconButtonUserWidget::SetBoxSize(const float Size) const 
{
	BoxRoot->SetWidthOverride(Size);
	BoxRoot->SetHeightOverride(Size);
}

void UIconButtonUserWidget::BroadcastClickEvent()
{
	OnIconButtonClickedDelegate.Broadcast(Index);
}
