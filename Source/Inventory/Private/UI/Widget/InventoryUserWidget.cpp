// Copyright Jack Kong.


#include "UI/Widget/InventoryUserWidget.h"
#include "UI/Widget/ProgressBarUserWidget.h"
#include "UI/WidgetController/InvWidgetController.h"
#include "Components/TextBlock.h"
#include "Engine/TargetPoint.h"
#include "Framework/InvPlayerController.h"
#include "Kismet/KismetTextLibrary.h"
#include "UI/Widget/ContentSwitcherUserWidget.h"

void UInventoryUserWidget::SetInvWidgetController(UInvWidgetController* InWidgetController)
{
	SetIsFocusable(true);
	
	InvWidgetController = InWidgetController;

	InvWidgetController->OnMoneyChangedDelegate.AddLambda(
		[this](const int32 NewMoney)
		{
			TextMoney->SetText(UKismetTextLibrary::Conv_IntToText(NewMoney));
		}
	);

	InvWidgetController->OnHealthChangedDelegate.AddLambda(
	[this](const float NewHealth)
		{
			HealthBar->SetValue(NewHealth);
		}
	);

	InvWidgetController->OnMaxHealthChangedDelegate.AddLambda(
	[this](const float NewMaxHealth)
		{
			HealthBar->SetMaxValue(NewMaxHealth);
		}
	);

	ContainerSwitcher->SetInvWidgetController(InvWidgetController);
	InvWidgetController->OnInventoryChangedDelegate.AddLambda(
		[this](const TArray<FOwnedItemCategory>& NewAllItems)
		{
			ContainerSwitcher->UpdateInventoryContainer(NewAllItems);
		}
	);
	
}

FReply UInventoryUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (Reply.IsEventHandled()) return Reply;

	if (InKeyEvent.GetKey() == EKeys::I || InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (AInvPlayerController* PC = Cast<AInvPlayerController>(InvWidgetController->PlayerController))
		{
			PC->ToggleInventoryWidget();
			return FReply::Handled();
		}
	}
	if (InKeyEvent.GetKey() == EKeys::F)
	{
		SpawnSkillOrbs(5);
	}
	if (InKeyEvent.GetKey() == EKeys::C)
	{
		TurnSkillOrbs();
	}
	return FReply::Unhandled();
}

void UInventoryUserWidget::SpawnSkillOrbs(const int32 Num)
{
	if (!SkillOrbs.IsEmpty()) return;
	const APawn* Pawn = InvWidgetController->PlayerController->GetPawn();
	const FVector Location = Pawn->GetActorLocation();
	const FRotator Rotator = Pawn->GetActorRotation();
	OrbsAttachActor = GetWorld()->SpawnActor<AActor>(ATargetPoint::StaticClass(), Location, FRotator());

	const FVector Forward = Pawn->GetActorForwardVector();
	Spread = 360.f / Num;

	for (int32 i=0;i<Num;i++)
	{
		const FVector SpawnLocation = Location + Forward.RotateAngleAxis(i * Spread, FVector::UpVector) * OrbOffsetDistance;
		AActor* Orb = GetWorld()->SpawnActor<AActor>(OrbActorClass, SpawnLocation, Rotator);
		Orb->AttachToActor(OrbsAttachActor, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		SkillOrbs.Add(Orb);
	}
	OrbsAttachActor->SetActorRelativeRotation(FRotator(20.f, 0.f, 0.f));
}

void UInventoryUserWidget::TurnSkillOrbs() const
{
	OrbsAttachActor->AddActorLocalRotation(FRotator(0.f, Spread, 0.f));
}

