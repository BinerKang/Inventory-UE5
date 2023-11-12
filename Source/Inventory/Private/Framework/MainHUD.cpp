// Copyright Jack Kong.


#include "Framework/MainHUD.h"

#include "UI/Widget/InventoryUserWidget.h"
#include "UI/Widget/OverlayUserWidget.h"
#include "UI/Widget/UserWidgetBase.h"
#include "UI/WidgetController/InvWidgetController.h"

void AMainHUD::InitAllWidgets(APlayerController* PC, APlayerState* PS)
{
	checkf(InventoryWidgetClass, TEXT("InventoryWidgetClass Property Not Set, Please fill it at BP_Aura_HUD"));
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass Property Not Set, Please fill it at BP_Aura_HUD"));
	checkf(InvWidgetControllerClass, TEXT("InvWidgetControllerClass Property Not Set, Please fill it at BP_Aura_HUD"));
	
	/* Init Inventory Widget and Controller */
	InvWidgetController = NewObject<UInvWidgetController>(this, InvWidgetControllerClass);
	InvWidgetController->SetParams(PC, PS);
	InvWidgetController->BindDelegates();
	
	InventoryWidget = CreateWidget<UInventoryUserWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget->SetInvWidgetController(InvWidgetController);

	// Create Overlay Widget
	OverlayWidget = CreateWidget<UOverlayUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetInvWidgetController(InvWidgetController);
	OverlayWidget->AddToViewport();

	InvWidgetController->BroadcastDefaultValues();
}
