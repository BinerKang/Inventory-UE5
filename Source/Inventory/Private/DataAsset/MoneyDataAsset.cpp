// Copyright Jack Kong.


#include "DataAsset/MoneyDataAsset.h"

FMoneyInfo UMoneyDataAsset::GetMoneyInfoByType(EMoneyType Type) const
{
	return MoneyInfos.FindChecked(Type);
}
