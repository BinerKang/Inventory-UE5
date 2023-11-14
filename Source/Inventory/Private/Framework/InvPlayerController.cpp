// Copyright Jack Kong.


#include "Framework/InvPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/HeroCharacter.h"
#include "Framework/MainHUD.h"
#include "UI/Widget/InventoryUserWidget.h"

void AInvPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(InputMappingContext, TEXT("[%s] InputMappingContext Not Set.Please fill it."), *GetNameSafe(this));
	checkf(MoveInputAction, TEXT("[%s] MoveInputAction Not Set.Please fill it."), *GetNameSafe(this));
	checkf(InteractInputAction, TEXT("[%s] InteractInputAction Not Set.Please fill it."), *GetNameSafe(this));
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	SetShowMouseCursor(true);
	DefaultMouseCursor = EMouseCursor::Default;

	SetNormalInputMode();
}

void AInvPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Component = CastChecked<UEnhancedInputComponent>(InputComponent);
	Component->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	Component->BindAction(InventoryInputAction, ETriggerEvent::Completed, this, &ThisClass::ToggleInventoryWidget);
	Component->BindAction(InteractInputAction, ETriggerEvent::Completed, this, &ThisClass::InteractKeyDown);
}

void AInvPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AInvPlayerController::ToggleInventoryWidget()
{
	
	if (const AMainHUD* HUD = Cast<AMainHUD>(GetHUD()))
	{
		if (bInventoryOpen)
		{
			if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(GetPawn()))
			{
				HeroCharacter->CloseLight();
			}
			HUD->GetInventoryWidget()->RemoveFromParent();
			SetNormalInputMode();
		}
		else
		{
			if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(GetPawn()))
			{
				HeroCharacter->OpenLight();
			}
			HUD->GetInventoryWidget()->AddToViewport(10);
			SetInventoryInputMode(HUD->GetInventoryWidget());
		}
		bInventoryOpen = !bInventoryOpen;
	}
	
}

void AInvPlayerController::InteractKeyDown()
{
	if (IPickupInterface* PickupInterface = Cast<IPickupInterface>(GetPawn()))
	{
		if (PickupInterface->GetOverlappingItem())
		{
			ServerDoInteract();
		}
	}
}

void AInvPlayerController::ServerDoInteract_Implementation()
{
	if (IPickupInterface* PickupInterface = Cast<IPickupInterface>(GetPawn()))
	{
		PickupInterface->AddToInventory();
	}
}

void AInvPlayerController::SetNormalInputMode()
{
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AInvPlayerController::SetInventoryInputMode(UUserWidget* FocusToWidget)
{
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(FocusToWidget->TakeWidget());
	
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}
