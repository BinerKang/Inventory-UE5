// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"


UCLASS()
class INVENTORY_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	void EquipWeapon(UStaticMesh* NewWeapon);
	void EquipShield(UStaticMesh* NewShield);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Shield;
};
