// Copyright Jack Kong.


#include "Character/CharacterBase.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{

	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Shield = CreateDefaultSubobject<UStaticMeshComponent>("Shield");
	Shield->SetupAttachment(GetMesh(), "ShieldHandSocket");
	Shield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACharacterBase::EquipWeapon(UStaticMesh* NewWeapon)
{
	Weapon->SetStaticMesh(NewWeapon);
}

void ACharacterBase::EquipShield(UStaticMesh* NewShield)
{
	Shield->SetStaticMesh(NewShield);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}
