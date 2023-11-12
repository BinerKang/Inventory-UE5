// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

class UWidgetControllerBase;
/**
 * 
 */
UCLASS()
class INVENTORY_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
};
