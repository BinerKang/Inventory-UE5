// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvGameModeBase.generated.h"

class AModelPositionActor;
/**
 * 
 */
UCLASS()
class INVENTORY_API AInvGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	FORCEINLINE TArray<AActor*> GetModelPositionActors() const { return ModelPositionActors; };

protected:
	virtual void BeginPlay() override;
	
	TArray<AActor*> ModelPositionActors;
};
