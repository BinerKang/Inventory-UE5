// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/UserWidgetBase.h"
#include "ProgressBarUserWidget.generated.h"

class UWrapBox;
/**
 * 
 */
UCLASS()
class INVENTORY_API UProgressBarUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	
	void SetMaxValue(const float NewMaxValue);
	
	void SetValue(const float NewValue);
	
protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> FillGroup;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UUserWidget> FillItemClass;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float MagnitudePerItem = 10;
	
private:

	float Value = 0.f;
	float MaxValue;
	
	void UpdateProgress();
	UUserWidget* CreateFillItemWidget(const float Percent);
};
