// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGFollowProjectile.h"

void AIGFollowProjectile::Init(const float InDamage, AActor& InTarget, const float MaxDistance, const float InSpeed, float InDuration, const EProjectileSpawnType InSpawnType)
{
	Damage = InDamage;
	OriginalPosition = GetActorLocation();
	TargetActor = InTarget;
	Speed = InSpeed;
	Duration = InDuration;
	SpawnType = InSpawnType;
}

void AIGFollowProjectile::Tick(float DeltaSeconds)
{
	const FVector CurrentLocation = GetActorLocation();
	const FVector TargetVector = (TargetActor->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
	const float DistancePerSecond = Speed * 100.f;
	const FVector FinalLocation = CurrentLocation + TargetVector * DistancePerSecond * DeltaSeconds;
	SetActorLocation(FinalLocation);
	Super::Tick(DeltaSeconds);
}
