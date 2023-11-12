// Copyright Jack Kong.


#include "UI/WidgetController/InvWidgetController.h"

#include "Framework/MainPlayerState.h"

void UInvWidgetController::BindDelegates()
{
	if (PlayerController->IsLocalController())
	{
		if (AMainPlayerState* PS = Cast<AMainPlayerState>(PlayerState))
		{
			PS->OnMoneyChangedDelegate.AddLambda(
				[this](const int32 NewMoney)
				{
					OnMoneyChangedDelegate.Broadcast(NewMoney);
				}
			);

			PS->OnHealthChangedDelegate.AddLambda(
				[this](const float NewHealth)
				{
					OnHealthChangedDelegate.Broadcast(NewHealth);
				}
			);
			
			PS->OnMaxHealthChangedDelegate.AddLambda(
				[this](const float NewMaxHealth)
				{
					OnMaxHealthChangedDelegate.Broadcast(NewMaxHealth);
				}
			);

			PS->OnInventoryChangedDelegate.AddLambda(
				[this](TArray<FOwnedItemCategory> NewInventory)
				{
					OnInventoryChangedDelegate.Broadcast(NewInventory);
				}
			);
		}
	}
	
}

void UInvWidgetController::BroadcastDefaultValues()
{
	if (PlayerController->IsLocalController())
	{
		if (AMainPlayerState* PS = Cast<AMainPlayerState>(PlayerState))
		{
			OnMoneyChangedDelegate.Broadcast(PS->GetMoney());
			OnMaxHealthChangedDelegate.Broadcast(PS->GetMaxHealth());
			OnHealthChangedDelegate.Broadcast(PS->GetHealth());
			OnInventoryChangedDelegate.Broadcast(PS->GetAllItems());
		}
	}
}
