// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGStraightProjectile.h"

void AIGStraightProjectile::Init(const float InDamage, const FVector& InTargetDirection, const float MaxDistance, const float InSpeed, const EProjectileSpawnType InSpawnType)
{
	Damage = InDamage;
	OriginalPosition = GetActorLocation();
	TargetPosition = OriginalPosition + InTargetDirection * MaxDistance;

	const float DistancePerSecond = InSpeed * 100.f;
	const float DistanceToTarget = (TargetPosition - OriginalPosition).Size2D();
	Duration = DistanceToTarget / DistancePerSecond;
	SpawnType = InSpawnType;
}

void AIGStraightProjectile::Tick(float DeltaSeconds)
{
	float Alpha = ElapsedTime / Duration;
	SetActorLocation(FMath::Lerp(OriginalPosition, TargetPosition, Alpha));
	Super::Tick(DeltaSeconds);
}
