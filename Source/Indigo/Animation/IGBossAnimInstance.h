// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGBossAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGenerateBossAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishBossAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishBossDeadDelegate)


enum EAttackPattern : uint32;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	TEnumAsByte<EAttackPattern> CurrentAttackPattern;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldPerformWeakNormalAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldPerformStrongNormalAttack : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldPerformCloseAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldPerformFloorAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldPerformFarAttack : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bIsDead : 1;
	
public:
	FOnGenerateBossAttackDelegate OnGenerateBossCloseAttack;
	FOnGenerateBossAttackDelegate OnGenerateBossFloorAttack;
	FOnGenerateBossAttackDelegate OnGenerateBossFarAttack;
	FOnFinishBossAttackDelegate OnFinishAttack;
	FOnFinishBossDeadDelegate OnFinishDead;
	
public:
	FORCEINLINE void SetSpeed(const float InValue) { Speed = InValue; }
	FORCEINLINE void Die() { bIsDead = true; }
	FORCEINLINE void StartWeakNormalAttack() { bShouldPerformWeakNormalAttack = true; }
	FORCEINLINE void StartStrongNormalAttack() { bShouldPerformStrongNormalAttack = true; }
	FORCEINLINE void StartCloseAttack() { bShouldPerformCloseAttack = true; }
	FORCEINLINE void StartFloorAttack() { bShouldPerformFloorAttack = true; }
	FORCEINLINE void StartFarAttack() { bShouldPerformFarAttack = true; }

	UFUNCTION()
	void AnimNotify_GenerateCloseAttack();

	UFUNCTION()
	void AnimNotify_GenerateFloorAttack();

	UFUNCTION()
	void AnimNotify_GenerateFarAttack();

	UFUNCTION()
	void AnimNotify_FinishAttack();

	UFUNCTION()
	void AnimNotify_BossDead();
};
