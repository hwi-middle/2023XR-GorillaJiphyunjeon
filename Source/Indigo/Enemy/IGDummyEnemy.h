// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGEnemyBase.h"
#include "IGDummyEnemy.generated.h"

class UIGBossAnimInstance;
class UIGPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class INDIGO_API AIGDummyEnemy : public AIGEnemyBase
{
	GENERATED_BODY()

public:
	AIGDummyEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<UIGBossAnimInstance> AnimInstance;
};
