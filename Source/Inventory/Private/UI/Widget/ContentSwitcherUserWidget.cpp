// Copyright Jack Kong.


#include "UI/Widget/ContentSwitcherUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Framework/MainPlayerState.h"
#include "UI/Widget/IconButtonUserWidget.h"
#include "UI/Widget/ItemSlotUserWidget.h"
#include "UI/Widget/ItemDetailUserWidget.h"
#include "UI/Widget/ActionMenuUserWidget.h"
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
				ChosenCategoryIndex = IconIndex;
				WidgetSwitcher->SetActiveWidgetIndex(ChosenCategoryIndex);
				UpdateChosenIndex();
			});
		
		IconGroup->AddChild(IconWidget);
		// Must After Added To IconGroup, Then Set Slot Alignment
		IconWidget->SetIndex(i, InWidgetController);
		
		AllIconButtonWidgets.Add(IconWidget);
	}
	UpdateChosenIndex();

	// Action Menu
	ActionMenu->OnActionMenuMouseLeaveDelegate.AddLambda([this]()
	{
		if (ItemDetail->IsVisible()) ItemDetail->SetVisibility(ESlateVisibility::Hidden);
	});
}

void UContentSwitcherUserWidget::UpdateChosenIndex()
{
	for (const UIconButtonUserWidget* IconWidget : AllIconButtonWidgets)
	{
		IconWidget->UpdateChosen(ChosenCategoryIndex);
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
				ItemWidget->SetItemInfo(ItemDataAsset->GetItemInfoByName(ItemInfo.EItemID), ItemInfo);

				ItemWidget->OnItemButtonHoveredDelegate.AddLambda([this](EPickableItemName EItemID)
				{
					ItemDetail->SetItemDetail(EItemID, InvWC);
					ItemDetail->SetVisibility(ESlateVisibility::HitTestInvisible);
				});

				ItemWidget->OnItemButtonUnHoveredDelegate.AddLambda([this](EPickableItemName EItemID)
				{
					// When Action Menu Is Visible, Do not hide
					if (!ActionMenu->IsVisible())
					{
						ItemDetail->SetVisibility(ESlateVisibility::Hidden);
					}
				});

				ItemWidget->OnItemButtonPressedDelegate.AddLambda([this](EPickableItemName EItemID)
				{
					ChosenItemID = EItemID;
					const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
					// Use Canvas Alignment to change relative position
					Cast<UCanvasPanelSlot>(ActionMenu->Slot)->SetPosition(MousePosition);
					const FItemCategoryInfo& CategoryInfo = InvWC->PickableItemDataAsset->GetCategoryInfoByEItemID(EItemID);
					ActionMenu->SetActionNames(EItemID, InvWC, CategoryInfo.UseActionName, CategoryInfo.DropActionName);
					ActionMenu->SetVisibility(ESlateVisibility::Visible);
				});
				
				Container->AddChild(ItemWidget);
			}
		}
	}
	
}
