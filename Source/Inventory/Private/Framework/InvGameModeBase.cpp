// Copyright Jack Kong.


#include "Framework/InvGameModeBase.h"

#include "Actor/ModelPositionActor.h"
#include "Kismet/GameplayStatics.h"


void AInvGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, AModelPositionActor::StaticClass(), ModelPositionActors);
}
