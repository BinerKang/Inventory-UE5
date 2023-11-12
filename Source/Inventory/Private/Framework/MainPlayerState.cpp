// Copyright Jack Kong.


#include "Framework/MainPlayerState.h"

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
	Health += InValue;
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