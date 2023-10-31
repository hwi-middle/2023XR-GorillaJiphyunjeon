// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGWispAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFinishWispAttackDelegate)
/**
 * 
 */
UCLASS()
class INDIGO_API UIGWispAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldAttack : 1;

public:
	FOnFinishWispAttackDelegate OnFinishHit;
	
	FORCEINLINE void OnHit() { bShouldAttack = true; }

	UFUNCTION()
	void AnimNotify_FinishHit();
	
};
