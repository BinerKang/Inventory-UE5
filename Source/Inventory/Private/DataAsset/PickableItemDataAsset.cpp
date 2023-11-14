// Copyright Jack Kong.


#include "DataAsset/PickableItemDataAsset.h"

FPickableItemInfo UPickableItemDataAsset::GetItemInfoByName(EPickableItemName Name) const
{
	if (Name == EPickableItemName::EPIN_Empty) return FPickableItemInfo();
	return ItemInfos.FindChecked(Name);
}

FItemCategoryInfo UPickableItemDataAsset::GetCategoryInfoByECategory(EPickableItemCategory Category) const
{
	return CategoryInfos.FindChecked(Category);
}

FItemCategoryInfo UPickableItemDataAsset::GetCategoryInfoByEItemID(EPickableItemName EItemID) const
{
	return CategoryInfos.FindChecked(GetItemInfoByName(EItemID).Category);
}
