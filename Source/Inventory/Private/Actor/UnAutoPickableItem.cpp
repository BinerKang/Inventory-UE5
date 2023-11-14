// Copyright Jack Kong.


#include "Actor/UnAutoPickableItem.h"

#include "Interface/PickupInterface.h"
#include "Components/BoxComponent.h"


void AUnAutoPickableItem::InitialItem(const EPickableItemName InEItemID, UPickableItemDataAsset* ItemDataAsset)
{
	EItemID = InEItemID;
	PickableItemDataAsset = ItemDataAsset;
	Mesh->SetStaticMesh(GetItemInfo().Mesh);
	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);
	Mesh->AddImpulse(GetActorForwardVector() * 200.f, NAME_None, true);
	BoxCollision->SetBoxExtent(FVector(60.f, 60.f, 32.f));

	GetWorld()->GetTimerManager().SetTimer(DisableTimer, this, &ThisClass::DisablePhysicalSimulation, SimulationSeconds, false);
}

void AUnAutoPickableItem::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor))
	{
		PickupInterface->SetOverlappingItem(this);	
	}
}

void AUnAutoPickableItem::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor))
	{
		PickupInterface->SetOverlappingItem(nullptr);	
	}
}

void AUnAutoPickableItem::DisablePhysicalSimulation()
{
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	BoxCollision->SetWorldLocation(Mesh->GetComponentLocation());
}
