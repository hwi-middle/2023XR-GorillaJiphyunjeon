// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGPlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFinishRollDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishPlayerAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnShouldGenerateProjectileDelegate)

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bIsAttacking : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bIsEnforced : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bIsDead : 1;

protected:
	UFUNCTION()
	void AnimNotify_RollEnd();
	
	UFUNCTION()
	void AnimNotify_AttackEnd();
	
	UFUNCTION()
	void AnimNotify_GenerateProjectile();
	
public:
	FOnFinishRollDelegate OnFinishRoll;
	FOnFinishPlayerAttackDelegate OnFinishAttack;
	FOnShouldGenerateProjectileDelegate OnShouldGenerateProjectile;

	FORCEINLINE void SetSpeed(const float InValue) { Speed = InValue; }
	FORCEINLINE void SetEnforced(const bool InValue) { bIsEnforced = InValue; }
	FORCEINLINE void Die() { bIsDead = true; }

	void StartRoll();
	void StartAttack();
};
