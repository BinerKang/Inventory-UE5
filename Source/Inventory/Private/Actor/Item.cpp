// Copyright Jack Kong.


#include "..\..\Public\Actor\Item.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(BoxCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToChannels(ECR_Block);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) return;
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::AItem::OnBoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::AItem::OnBoxEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoTick && WasRecentlyRendered(0.1))
	{
		if (Amplitude > 0.f)
		{
			RunningTime += DeltaTime;
			AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
		}

		if (RotationRate > 0.f)
		{
			AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
		}
	}
}

void AItem::Destroyed()
{
	Super::Destroyed();
	if (DestroySound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
	}
}

FPickableItemInfo AItem::GetItemInfo() const
{
	return PickableItemDataAsset->GetItemInfoByName(EItemID);
}

void AItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AItem::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

float AItem::TransformedSin() const
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos() const
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

