// Copyright Jack Kong.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

class UCharacterMovementComponent;
class ACharacterBase;
/**
 * 
 */
UCLASS()
class INVENTORY_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacterBase> CharacterBase;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float GroundSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	bool IsFalling;
};
