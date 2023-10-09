// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGEnemyBase.h"
#include "IGBoss.generated.h"

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

public:
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }
	void PerformCloseAttack();
	void GenerateCloseAttack();

};
