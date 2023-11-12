// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartUserWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UHeartUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPercent(float Percent) const;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ImageHeart;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UTexture2D> FullHeartTexture;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UTexture2D> HalfHeartTexture;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TObjectPtr<UTexture2D> EmptyHeartTexture;
	
};
