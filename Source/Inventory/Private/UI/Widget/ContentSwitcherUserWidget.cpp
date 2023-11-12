// Copyright Jack Kong.


#include "UI/Widget/ContentSwitcherUserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "Framework/MainPlayerState.h"
#include "UI/Widget/IconButtonUserWidget.h"
#include "UI/Widget/ItemSlotUserWidget.h"
#include "UI/Widget/ItemDetailUserWidget.h"
#include "UI/WidgetController/InvWidgetController.h"

void UContentSwitcherUserWidget::SetInvWidgetController(UInvWidgetController* InWidgetController)
{
	InvWC = InWidgetController;

	checkf(IconButtonWidgetClass, TEXT("[%s] UIconButtonUserWidget Not Set.Please Fill it."), *GetName());
	if (!IsValid(IconButtonWidgetClass)) return;

	// Clear Old Widgets
	for (UIconButtonUserWidget* Widget : AllIconButtonWidgets)
	{
		IconGroup->RemoveChild(Widget);
	}
	AllIconButtonWidgets.Empty();
	
	for (int32 i=0;i<ContentTypeCount;i++)
	{
		UIconButtonUserWidget* IconWidget = CreateWidget<UIconButtonUserWidget>(this, IconButtonWidgetClass);
		// Bind Click Event
		IconWidget->OnIconButtonClickedDelegate.AddLambda(
			[this](const int32 IconIndex)
			{
				ChosenIndex = IconIndex;
				WidgetSwitcher->SetActiveWidgetIndex(ChosenIndex);
				UpdateChosenIndex();
			});
		
		IconGroup->AddChild(IconWidget);
		// Add IconGroup Then Set Slot Alignment
		IconWidget->SetIndex(i, InWidgetController);
		
		AllIconButtonWidgets.Add(IconWidget);
	}
	UpdateChosenIndex();
}

void UContentSwitcherUserWidget::UpdateChosenIndex()
{
	for (const UIconButtonUserWidget* IconWidget : AllIconButtonWidgets)
	{
		IconWidget->UpdateChosen(ChosenIndex);
	}
}

void UContentSwitcherUserWidget::UpdateInventoryContainer(const TArray<FOwnedItemCategory>& AllItems)
{
	EatableContainer->ClearChildren();
	ShieldContainer->ClearChildren();
	WeaponContainer->ClearChildren();

	const UPickableItemDataAsset* ItemDataAsset = InvWC->PickableItemDataAsset;
	
	UWrapBox* Container = nullptr;
	for (const FOwnedItemCategory& CategoryItems: AllItems)
	{
		switch (CategoryItems.Category)
		{
		case EPickableItemCategory::EPIC_Eatable: Container = EatableContainer; break;
		case EPickableItemCategory::EPIC_Shield: Container = ShieldContainer; break;
		case EPickableItemCategory::EPIC_Weapon: Container = WeaponContainer; break;
		}

		if (Container)
		{
			for (const FOwnedItemInfo& ItemInfo : CategoryItems.ItemInfos)
			{
				UItemSlotUserWidget* ItemWidget = CreateWidget<UItemSlotUserWidget>(this, ItemSlotWidgetClass);
				ItemWidget->SetItemInfo(ItemDataAsset->GetItemInfoByName(ItemInfo.EItemID).Icon, ItemInfo.Quantity, ItemInfo.EItemID);

				ItemWidget->OnItemButtonHoveredDelegate.AddLambda([this](EPickableItemName EItemID)
				{
					ItemDetail->SetItemDetail(EItemID, InvWC);
					ItemDetail->SetVisibility(ESlateVisibility::HitTestInvisible);
				});

				ItemWidget->OnItemButtonUnHoveredDelegate.AddLambda([this](EPickableItemName EItemID)
				{
					ItemDetail->SetVisibility(ESlateVisibility::Hidden);
				});

				Container->AddChild(ItemWidget);
			}
		}
	}
	
}
