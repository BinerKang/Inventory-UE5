// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModelPositionActor.generated.h"

class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class INVENTORY_API AModelPositionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AModelPositionActor();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> ArrowComponent;

};
