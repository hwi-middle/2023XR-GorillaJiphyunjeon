// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossAnimInstance.h"

void UIGBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	InterpolatedSpeed = FMath::FInterpTo(InterpolatedSpeed, Speed, DeltaSeconds, 10.f);
}

void UIGBossAnimInstance::AnimNotify_GenerateCloseAttack()
{
	OnGenerateBossCloseAttack.Broadcast();
}

void UIGBossAnimInstance::AnimNotify_EndCloseAttack()
{
	OnFinishAttack.Broadcast();
	bShouldPerformCloseAttack = false;
}

void UIGBossAnimInstance::AnimNotify_BossDead()
{
	OnFinishDead.Broadcast();
}
