// Copyright Jack Kong.


#include "Actor/ModelPositionActor.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

AModelPositionActor::AModelPositionActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SetRootComponent(CapsuleComponent);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->SetupAttachment(GetRootComponent());
	
}

