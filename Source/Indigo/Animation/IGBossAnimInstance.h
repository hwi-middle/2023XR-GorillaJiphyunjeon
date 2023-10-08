// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float InterpolatedSpeed;
	
public:
	FORCEINLINE void SetSpeed(const float InValue) { Speed = InValue; }

};
