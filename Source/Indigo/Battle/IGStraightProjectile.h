// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGProjectileBase.h"
#include "IGStraightProjectile.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API AIGStraightProjectile : public AIGProjectileBase
{
	GENERATED_BODY()
public:
	void Init(const float InDamage, const FVector& InTargetDirection, const float MaxDistance, const float InSpeed, const EProjectileSpawnType InSpawnType);

protected:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY()
	FVector OriginalPosition;
	
	UPROPERTY()
	FVector TargetPosition;

};
