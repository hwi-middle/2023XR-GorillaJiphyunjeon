// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGProjectileBase.h"
#include "IGFollowProjectile.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class INDIGO_API AIGFollowProjectile : public AIGProjectileBase
{
	GENERATED_BODY()
public:
	AIGFollowProjectile();
	void Init(const float InDamage, AActor* InTarget, const float MaxDistance, const float InSpeed, float InDuration, const EProjectileSpawnType InSpawnType);

protected:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
	
	UPROPERTY()
	float Speed;
	
	UPROPERTY()
	FVector OriginalPosition;
	
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
};
