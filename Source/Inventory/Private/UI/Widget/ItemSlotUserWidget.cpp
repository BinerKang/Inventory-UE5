// Copyright Jack Kong.


#include "UI/Widget/ItemSlotUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UItemSlotUserWidget::SetItemInfo(UTexture2D* Icon, int32 Quantity, EPickableItemName InItemId)
{
	FButtonStyle& ButtonStyle = const_cast<FButtonStyle&>(ItemButton->GetStyle());
	ButtonStyle.Normal.SetResourceObject(Icon);
	ButtonStyle.Hovered.SetResourceObject(Icon);
	ButtonStyle.Disabled.SetResourceObject(Icon);
	ButtonStyle.Pressed.SetResourceObject(Icon);

	QuantityText->SetText(UKismetTextLibrary::Conv_IntToText(Quantity));

	EItemID = InItemId;

	ItemButton->OnHovered.AddDynamic(this, &ThisClass::OnItemButtonHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &ThisClass::OnItemButtonUnHovered);
}

void UItemSlotUserWidget::OnItemButtonHovered()
{
	OnItemButtonHoveredDelegate.Broadcast(EItemID);
}

void UItemSlotUserWidget::OnItemButtonUnHovered()
{
	OnItemButtonUnHoveredDelegate.Broadcast(EItemID);
}
