// Copyright Jack Kong.


#include "UI/Widget/ItemSlotUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DataAsset/PickableItemDataAsset.h"
#include "Framework/MainPlayerState.h"
#include "Kismet/KismetTextLibrary.h"

void UItemSlotUserWidget::SetItemInfo(const FPickableItemInfo& ItemInfo, const FOwnedItemInfo& OwnedItemInfo)
{

	FButtonStyle& ButtonStyle = const_cast<FButtonStyle&>(ItemButton->GetStyle());
	ButtonStyle.Normal.SetResourceObject(ItemInfo.Icon);
	ButtonStyle.Hovered.SetResourceObject(ItemInfo.Icon);
	ButtonStyle.Disabled.SetResourceObject(ItemInfo.Icon);
	ButtonStyle.Pressed.SetResourceObject(ItemInfo.Icon);

	QuantityText->SetText(UKismetTextLibrary::Conv_IntToText(OwnedItemInfo.Quantity));

	EItemID = OwnedItemInfo.EItemID;

	if (OwnedItemInfo.bIsEquipped)
	{
		EquippedBgImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		EquippedBgImage->SetVisibility(ESlateVisibility::Hidden);
	}

	ItemButton->OnHovered.AddDynamic(this, &ThisClass::OnItemButtonHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &ThisClass::OnItemButtonUnHovered);
	ItemButton->OnPressed.AddDynamic(this, &ThisClass::OnItemButtonPressed);
}

void UItemSlotUserWidget::OnItemButtonHovered()
{
	HoverBorderImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	OnItemButtonHoveredDelegate.Broadcast(EItemID);
}

void UItemSlotUserWidget::OnItemButtonUnHovered()
{
	HoverBorderImage->SetVisibility(ESlateVisibility::Hidden);
	OnItemButtonUnHoveredDelegate.Broadcast(EItemID);
}

void UItemSlotUserWidget::OnItemButtonPressed()
{
	OnItemButtonPressedDelegate.Broadcast(EItemID);
}
