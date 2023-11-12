// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InvPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class INVENTORY_API AInvPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleInventoryWidget();

	UFUNCTION()
	void InteractKeyDown();
	
	UFUNCTION(Server, Reliable)
	void ServerDoInteract();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InventoryInputAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractInputAction;
	
private:

	void Move(const FInputActionValue& InputActionValue) ;

	void SetNormalInputMode();
	void SetInventoryInputMode(UUserWidget* FocusToWidget);
	
	UPROPERTY()
	bool bInventoryOpen = false;
};
