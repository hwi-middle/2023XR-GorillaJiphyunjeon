// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerAnimInstance.h"

void UIGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	InterpolatedSpeed = FMath::FInterpTo(InterpolatedSpeed, Speed, DeltaSeconds, 10.f);
}

