// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGBossAnimInstance.generated.h"

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
	uint8 bShouldPerformCloseAttack : 1;
	
public:
	FORCEINLINE void SetSpeed(const float InValue) { Speed = InValue; }
	FORCEINLINE void StartCloseAttack() { bShouldPerformCloseAttack = true; }
};
