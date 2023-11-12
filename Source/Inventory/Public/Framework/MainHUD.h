// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UInventoryUserWidget;
class UOverlayUserWidget;
class UInvWidgetController;
class UWidgetControllerBase;
class UUserWidgetBase;
/**
 * 
 */
UCLASS()
class INVENTORY_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitAllWidgets(APlayerController* PC, APlayerState* PS);

	FORCEINLINE UInventoryUserWidget* GetInventoryWidget() const { return InventoryWidget; }
	FORCEINLINE UOverlayUserWidget* GetOverlayWidget() const { return OverlayWidget; }
	FORCEINLINE UInvWidgetController* GetInvWidgetController() const { return InvWidgetController; }
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UInventoryUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UOverlayUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TSubclassOf<UInvWidgetController> InvWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UInvWidgetController> InvWidgetController;

	UPROPERTY()
	TObjectPtr<UInventoryUserWidget> InventoryWidget;

	UPROPERTY()
	TObjectPtr<UOverlayUserWidget> OverlayWidget;
};
