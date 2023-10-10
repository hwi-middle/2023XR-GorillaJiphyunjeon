// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGEnemyBase.h"
#include "IGBoss.generated.h"

class UIGBossGimmickDataAsset;
DECLARE_MULTICAST_DELEGATE(FOnFinishBossCloseAttackDelegate)

class UIGBossAnimInstance;
class UIGPlayerAnimInstance;
/**
 * 
 */

UENUM(BlueprintType)
enum EAttackPattern : uint32
{
	None,
	Close,
	Far,
	Floor,
};

UCLASS()
class INDIGO_API AIGBoss : public AIGEnemyBase
{
	GENERATED_BODY()

public:
	AIGBoss();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<UIGBossAnimInstance> AnimInstance;

	UPROPERTY()
	float StoppingDistance;

	// UPROPERTY()
	// EAttackPattern CurrentAttackPattern;

	// 기믹 데이터
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGBossGimmickDataAsset> GimmickDataAsset;

	// 근거리 패턴
	UPROPERTY(VisibleAnywhere)
	uint32 CloseAttack_SpikeNum;
	
	UPROPERTY(VisibleAnywhere)
	float CloseAttack_HandRadius;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_Damage;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeTimeGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDistanceGap;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDuration;

	UPROPERTY(VisibleAnywhere)
	float CloseAttack_SpikeDestroyDelay;

public:
	FOnFinishBossCloseAttackDelegate OnFinishBossCloseAttack;

public:
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }
	void PerformCloseAttack();
	void GenerateCloseAttack();
	void EndCloseAttack();
};
