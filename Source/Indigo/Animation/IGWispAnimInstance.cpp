// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/Animation/IGWispAnimInstance.h"

void UIGWispAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{	
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UIGWispAnimInstance::AnimNotify_FinishHit()
{
	OnFinishHit.Broadcast();
	bShouldAttack = false;
}

void UIGWispAnimInstance::AnimNotify_FinishDash()
{
	OnFinishDash.Broadcast();
	bShouldDash = false;
	bShouldRetreat = true;
}

void UIGWispAnimInstance::AnimNotify_FinishExplosion()
{
	OnFinishBomb.Broadcast();
	bShouldExplosion = false;
}

void UIGWispAnimInstance::AnimNotify_Explosion()
{
	OnWispExplosion.Broadcast();
}

void UIGWispAnimInstance::AnimNotify_FinishRetreat()
{
	OnFinishRetreat.Broadcast();
	bShouldRetreat = false;
}
