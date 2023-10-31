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
