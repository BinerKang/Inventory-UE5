// Copyright Jack Kong.


#include "Anim/AnimInstanceBase.h"

#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
}

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterBase = Cast<ACharacterBase>(TryGetPawnOwner());
	if (CharacterBase)
	{
		MovementComponent = CharacterBase->GetCharacterMovement();
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		GroundSpeed = MovementComponent->Velocity.Size2D();
		IsFalling = MovementComponent->IsFalling();
	}
}
