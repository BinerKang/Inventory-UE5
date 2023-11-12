// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "WidgetControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:

	void SetParams(APlayerController* PC, APlayerState* PS);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;
};
