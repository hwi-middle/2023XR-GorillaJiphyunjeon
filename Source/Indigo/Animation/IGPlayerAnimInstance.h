// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float InterpolatedSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bIsRolling : 1;

protected:
	UFUNCTION()
	void AnimNotify_RollEnd();
	
public:
	FORCEINLINE void SetSpeed(const float InValue) { Speed = InValue; }
	void StartRoll() { bIsRolling = true; }
};
