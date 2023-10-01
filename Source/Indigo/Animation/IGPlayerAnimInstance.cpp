// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerAnimInstance.h"

void UIGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	InterpolatedSpeed = FMath::FInterpTo(InterpolatedSpeed, Speed, DeltaSeconds, 10.f);
}

void UIGPlayerAnimInstance::AnimNotify_RollEnd()
{
	bIsRolling = false;
	OnFinishRoll.Broadcast();
}

void UIGPlayerAnimInstance::AnimNotify_AttackEnd()
{
	bIsAttacking = false;
	OnFinishAttack.Broadcast();
}

void UIGPlayerAnimInstance::StartRoll()
{
	bIsRolling = true;
}

void UIGPlayerAnimInstance::StartAttack()
{
	bIsAttacking = true;
}

