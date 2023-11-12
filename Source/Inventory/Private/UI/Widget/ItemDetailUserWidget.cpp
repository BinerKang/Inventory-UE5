// Copyright Jack Kong.


#include "UI/Widget/ItemDetailUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DataAsset/PickableItemDataAsset.h"
#include "Kismet/KismetTextLibrary.h"
#include "UI/WidgetController/InvWidgetController.h"

void UItemDetailUserWidget::SetItemDetail(EPickableItemName InEItemID, UInvWidgetController* InvWC)
{
	if (EItemID == InEItemID && EItemID != EPickableItemName::EPIN_Empty) return;
	EItemID = InEItemID;
	const FPickableItemInfo& ItemInfo = InvWC->PickableItemDataAsset->GetItemInfoByName(EItemID);
	TextName->SetText(ItemInfo.Name);
	TextPower->SetText(UKismetTextLibrary::Conv_DoubleToText(ItemInfo.Power, HalfFromZero));
	TextDescription->SetText(ItemInfo.Description);
	ImageIcon->SetBrushFromTexture(InvWC->PickableItemDataAsset->GetCategoryInfoByECategory(ItemInfo.Category).Icon);
}
