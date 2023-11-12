// Copyright Jack Kong.


#include "UI/Widget/HeartUserWidget.h"
#include "Components/Image.h"


void UHeartUserWidget::SetPercent(float Percent) const
{
	UTexture2D* HeartTexture = EmptyHeartTexture;
	if (Percent >= 1.f)
	{
		HeartTexture = FullHeartTexture;
	}
	else if (Percent >= 0.5f)
	{
		HeartTexture = HalfHeartTexture;
	}
	
	ImageHeart->SetBrushFromTexture(HeartTexture);
}
