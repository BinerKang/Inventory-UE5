// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API AInvGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:


protected:
	virtual void BeginPlay() override;
};
