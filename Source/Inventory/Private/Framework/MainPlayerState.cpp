// Copyright Jack Kong.


#include "Framework/MainPlayerState.h"

#include "Actor/UnAutoPickableItem.h"
#include "Character/CharacterBase.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

AMainPlayerState::AMainPlayerState()
{
	AllItems.Add(FOwnedItemCategory(EPickableItemCategory::EPIC_Eatable));// Index 0: --Eatable
	AllItems.Add(FOwnedItemCategory(EPickableItemCategory::EPIC_Shield));// Index 1: --Shield
	AllItems.Add(FOwnedItemCategory(EPickableItemCategory::EPIC_Weapon));// Index 2: --Weapon
}

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Money);
	DOREPLIFETIME(ThisClass, Health);
	DOREPLIFETIME(ThisClass, MaxHealth);
	DOREPLIFETIME(ThisClass, AllItems);

}

void AMainPlayerState::AddToMoney(const int32 InAmount)
{
	Money += InAmount;

	OnMoneyChangedDelegate.Broadcast(Money);
}

void AMainPlayerState::AddToHealth(const float InValue)
{
	Health = FMath::Clamp(Health + InValue, 0.f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(Health);
}

void AMainPlayerState::AddToMaxHealth(const float InValue)
{
	MaxHealth += InValue;
	OnMaxHealthChangedDelegate.Broadcast(MaxHealth);
}

void AMainPlayerState::AddToOwnedItems(const FPickableItemInfo& Info, const EPickableItemName EItemID)
{
	int32 Index = 0;
	
	switch (Info.Category)
	{
	case EPickableItemCategory::EPIC_Eatable: break;
	case EPickableItemCategory::EPIC_Shield: Index = 1; break;
	case EPickableItemCategory::EPIC_Weapon: Index = 2; break;
	}
	
	TArray<FOwnedItemInfo>& CategoryItems = AllItems[Index].ItemInfos;
	for (int32 i=0;i<CategoryItems.Num();i++)
	{
		if (CategoryItems[i].EItemID == EItemID)
		{
			// TODO : Check Max Stack
			CategoryItems[i].Quantity++;
			OnInventoryChangedDelegate.Broadcast(AllItems);
			return;
		}
	}
	
	// Not Found, Add a new
	CategoryItems.Add(FOwnedItemInfo(EItemID, 1));

	OnInventoryChangedDelegate.Broadcast(AllItems);
}

void AMainPlayerState::UseItem(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo)
{
	switch (UsedItemInfo.Category)
	{
	case EPickableItemCategory::EPIC_Eatable:
		AddToHealth(UsedItemInfo.Power);
		ConsumeItem(EItemID, UsedItemInfo);
		break;
	case EPickableItemCategory::EPIC_Shield:
		// TODO: Use Interface Instead
		if (ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetPawn()))
		{
			CharacterBase->EquipShield(UsedItemInfo.Mesh);
			UpdateEquipState(EItemID, UsedItemInfo);
		}
		break;
	case EPickableItemCategory::EPIC_Weapon:
		// TODO: Use Interface Instead
		if (ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetPawn()))
		{
			CharacterBase->EquipWeapon(UsedItemInfo.Mesh);
			UpdateEquipState(EItemID, UsedItemInfo);
		}
		break;
	}
	
}

void AMainPlayerState::DropItem(EPickableItemName EItemID, UPickableItemDataAsset* ItemDataAsset)
{
	const FPickableItemInfo& UsedItemInfo = ItemDataAsset->GetItemInfoByName(EItemID);
	// Spawn Item
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * 100.f);
	AUnAutoPickableItem* Item = GetWorld()->SpawnActorDeferred<AUnAutoPickableItem>(AUnAutoPickableItem::StaticClass(), SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Item->InitialItem(EItemID, ItemDataAsset, GetPawn()->GetActorForwardVector());
	Item->FinishSpawning(SpawnTransform);
	
	ConsumeItem(EItemID, UsedItemInfo);

}

void AMainPlayerState::ConsumeItem(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo)
{
	// Reduce Quantity or remove
	for (FOwnedItemCategory& CategoryItems : AllItems)
	{
		if (CategoryItems.Category == UsedItemInfo.Category)
		{
			int32 NeedRemoveIndex = -1;
			for (int32 i=0;i<CategoryItems.ItemInfos.Num();i++)
			{
				if (CategoryItems.ItemInfos[i].EItemID == EItemID)
				{
					// Remove this item
					if (CategoryItems.ItemInfos[i].Quantity <= 1) 
					{
						NeedRemoveIndex = i;
					}
					else
					{
						CategoryItems.ItemInfos[i].Quantity--;
						OnInventoryChangedDelegate.Broadcast(AllItems);
						return;
					}
				}
			}
			if (NeedRemoveIndex >= 0)
			{
				// If Equipped Item ,removed, need remove Character's .
				if (CategoryItems.ItemInfos[NeedRemoveIndex].bIsEquipped)
				{
					if (ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetPawn()))
					{
						if (UsedItemInfo.Category == EPickableItemCategory::EPIC_Weapon)
						{
							CharacterBase->EquipWeapon(nullptr);
						}
						else if (UsedItemInfo.Category == EPickableItemCategory::EPIC_Shield)
						{
							CharacterBase->EquipShield(nullptr);
						}
					}
				}
				CategoryItems.ItemInfos.RemoveAt(NeedRemoveIndex);
				OnInventoryChangedDelegate.Broadcast(AllItems);
			}
			break;
		}
	}
}

void AMainPlayerState::UpdateEquipState(EPickableItemName EItemID, const FPickableItemInfo& UsedItemInfo)
{
	for (FOwnedItemCategory& CategoryItems : AllItems)
	{
		if (CategoryItems.Category == UsedItemInfo.Category)
		{
			for (int32 i=0;i<CategoryItems.ItemInfos.Num();i++)
			{
				if (CategoryItems.ItemInfos[i].EItemID == EItemID)
				{
					CategoryItems.ItemInfos[i].bIsEquipped = true;
				}
				else
				{
					CategoryItems.ItemInfos[i].bIsEquipped = false;
				}
			}
			OnInventoryChangedDelegate.Broadcast(AllItems);
			return;
		}
	}
}

void AMainPlayerState::OnRep_Money(int32 OldMoney) const
{
	OnMoneyChangedDelegate.Broadcast(Money);
}

void AMainPlayerState::OnRep_Health(float OldHealth) const
{
	OnHealthChangedDelegate.Broadcast(Health);
}

void AMainPlayerState::OnRep_MaxHealth(float OldMaxHealth) const
{
	OnMaxHealthChangedDelegate.Broadcast(MaxHealth);
}

void AMainPlayerState::OnRep_AllItems(TArray<FOwnedItemCategory> OldItems) const
{
	OnInventoryChangedDelegate.Broadcast(AllItems);
}