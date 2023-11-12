// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPickableItemName : uint8
{
	EPIN_Empty UMETA(DisplayName = "Empty"),
	EPIN_Apple UMETA(DisplayName = "Eatable-Apple"),
	EPIN_Banana UMETA(DisplayName = "Eatable-MightyBananas"),
	EPIN_Pumpkin UMETA(DisplayName = "Eatable-Pumpkin"),
	EPIN_Watermelon UMETA(DisplayName = "Eatable-Watermelon"),
	EPIN_Pepper UMETA(DisplayName = "Eatable-Pepper"),
	EPIN_DayBreaker UMETA(DisplayName = "Shield-DayBreaker"),
	EPIN_RoyalGuard UMETA(DisplayName = "Shield-RoyalGuard"),
	EPIN_SteelLizal UMETA(DisplayName = "Shield-SteelLizal"),
	EPIN_BlizzardRod UMETA(DisplayName = "Weapon-BlizzardRod"),
	EPIN_KnightBroad UMETA(DisplayName = "Weapon-KnightBroad"),
	EPIN_SpikedBoko UMETA(DisplayName = "Weapon-SpikedBoko")

};

UENUM(BlueprintType)
enum class EPickableItemCategory : uint8
{
	EPIC_Weapon UMETA(DisplayName = "Weapon"),
	EPIC_Shield UMETA(DisplayName = "Shield"),
	EPIC_Eatable UMETA(DisplayName = "Eatable")
};