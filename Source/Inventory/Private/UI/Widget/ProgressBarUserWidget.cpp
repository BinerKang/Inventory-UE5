// Copyright Jack Kong.


#include "UI/Widget/ProgressBarUserWidget.h"
#include "Components/WrapBox.h"
#include "UI/Widget/HeartUserWidget.h"

void UProgressBarUserWidget::SetMaxValue(const float NewMaxValue)
{
	MaxValue = NewMaxValue / MagnitudePerItem;
	UpdateProgress();
}

void UProgressBarUserWidget::SetValue(const float NewValue)
{
	Value = NewValue / MagnitudePerItem;
	UpdateProgress();
}

void UProgressBarUserWidget::UpdateProgress()
{
	FillGroup->ClearChildren();
	
	float LocalValue  = Value;

	int32 Counter = 0;
	while(true)
	{
		if (LocalValue >= 1.f)
		{
			FillGroup->AddChild(CreateFillItemWidget(1.f));
			Counter++;
		}
		else if (LocalValue > 0.f)
		{
			FillGroup->AddChild(CreateFillItemWidget(LocalValue));
			Counter++;
		}
		else
		{
			break;
		}
		LocalValue--;
	}

	float LeaveValue = MaxValue - Counter;
	while(true)
	{
		LeaveValue--;
		if (LeaveValue < 0.f) break;
		FillGroup->AddChild(CreateFillItemWidget(0.f));
	}
	
}

UUserWidget* UProgressBarUserWidget::CreateFillItemWidget(const float Percent)
{
	UHeartUserWidget* HeartWidget = CreateWidget<UHeartUserWidget>(this, FillItemClass);
	HeartWidget->SetPercent(Percent);
	return HeartWidget;
}
