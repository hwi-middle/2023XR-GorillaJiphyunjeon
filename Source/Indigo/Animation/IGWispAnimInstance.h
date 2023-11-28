// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGWispAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFinishWispAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishWispDashDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishWispBombDelegate)
DECLARE_MULTICAST_DELEGATE(FOnFinishWispRetreatDelegate)
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldDash : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldRetreat : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bShouldExplosion : 1;

public:
	FOnFinishWispAttackDelegate OnFinishHit;
	FOnFinishWispDashDelegate OnFinishDash;
	FOnFinishWispBombDelegate OnFinishBomb;
	FOnFinishWispBombDelegate OnWispExplosion;
	FOnFinishWispRetreatDelegate OnFinishRetreat;
	
	FORCEINLINE bool GetIsExplosion() const { return bShouldExplosion; }
	
	FORCEINLINE void OnHit() { bShouldAttack = true; }
	FORCEINLINE void OnExplosion() { bShouldExplosion = true; }
	FORCEINLINE void OnDash() { bShouldDash = true; }
	FORCEINLINE void OnRetreat() { bShouldRetreat = true; }
	//대쉬중 강제 해제
	FORCEINLINE void OnDashFinish() { bShouldDash = false; }

	UFUNCTION()
	void AnimNotify_FinishHit();
	
	UFUNCTION()
	void AnimNotify_FinishDash();
	
	UFUNCTION()
	void AnimNotify_FinishExplosion();
	
	UFUNCTION()
	void AnimNotify_Explosion();
	
	UFUNCTION()
	void AnimNotify_FinishRetreat();
	
};
