// Copyright Jack Kong.


#include "Character/HeroCharacter.h"

#include "Camera/CameraComponent.h"
#include "Framework/InvPlayerController.h"
#include "Framework/MainHUD.h"
#include "Framework/MainPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/Widget/OverlayUserWidget.h"
#include "Actor/Item.h"

AHeroCharacter::AHeroCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetUsingAbsoluteRotation(true);
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bConstrainToPlane = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitHUD();
}

void AHeroCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(ThisClass, OverlappingItem, COND_OwnerOnly);
}

void AHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitHUD();
}

void AHeroCharacter::AddMoney(const int32 InAmount)
{
	Cast<AMainPlayerState>(GetPlayerState())->AddToMoney(InAmount);
}

void AHeroCharacter::AddToInventory()
{
	if (OverlappingItem)
	{
		Cast<AMainPlayerState>(GetPlayerState())->AddToOwnedItems(OverlappingItem->GetItemInfo(), OverlappingItem->GetItemID());
        OverlappingItem->Destroy();
	}

}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AHeroCharacter::InitHUD() const
{
	if (AInvPlayerController* PC = Cast<AInvPlayerController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			HUD->InitAllWidgets(PC, GetPlayerState());
		}
	}
}

void AHeroCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
	ChangePickupWidgetVisibility();
}

void AHeroCharacter::OnRep_OverlappingItem(AItem* LastOverlappingItem)
{
	ChangePickupWidgetVisibility();
}

void AHeroCharacter::ChangePickupWidgetVisibility() const
{
	if (OverlappingItem == nullptr) //  Hide Interaction Widget
	{
		SetPickupWidgetVisibility(false);
	}
	else // Show  Interaction Widget
	{
		SetPickupWidgetVisibility(true, OverlappingItem->GetItemID());
	}
}

void AHeroCharacter::SetPickupWidgetVisibility(bool bIsShow, EPickableItemName EItemID) const
{
	if (const AInvPlayerController* PC = Cast<AInvPlayerController>(GetController()))
	{
		if (const AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			HUD->GetOverlayWidget()->SetPickupHintVisibility(bIsShow, EItemID);
		}
	}
}
