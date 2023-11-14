// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGFollowProjectile.h"
#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/KismetMathLibrary.h"

AIGFollowProjectile::AIGFollowProjectile()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Boss_Attack_LongRange_Projectile03.NS_Boss_Attack_LongRange_Projectile03'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	RootComponent = NiagaraComp;
}

void AIGFollowProjectile::Init(const float InDamage, AActor* InTarget, const float InSpeed, float InDuration, const EProjectileSpawnType InSpawnType)
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

	const FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
	SetActorRotation(Rot + FRotator(0.f, -90.f, 0.f));

	Super::Tick(DeltaSeconds);
}
