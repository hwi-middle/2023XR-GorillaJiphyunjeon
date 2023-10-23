// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProjectile.h"

#include "Engine/DamageEvents.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGProjectile::AIGProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(
		TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
		{
			Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
			Mesh->SetStaticMesh(MeshRef);
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			RootComponent = Mesh;
		}, EAssertionLevel::None);
}

void AIGProjectile::Init(const float InDamage, const FVector& InTargetDirection, const float MaxDistance, const float InSpeed, const EProjectileType InType)
{
	Damage = InDamage;
	OriginalPosition = GetActorLocation();
	TargetPosition = OriginalPosition + InTargetDirection * MaxDistance;

	const float DistancePerSecond = InSpeed * 100.f;
	const float DistanceToTarget = (TargetPosition - OriginalPosition).Size2D();
	Duration = DistanceToTarget / DistancePerSecond;
	ProjectileType = InType;
}

// Called when the game starts or when spawned
void AIGProjectile::BeginPlay()
{
	Super::BeginPlay();
	ElapsedTime = 0;
}

// Called every frame
void AIGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime > Duration)
	{
		Destroy();
	}

	float Alpha = ElapsedTime / Duration;
	SetActorLocation(FMath::Lerp(OriginalPosition, TargetPosition, Alpha));

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 50.f;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (!bHit)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("투사체 충돌 검출: %s"), *Result.GetActor()->GetName());

	switch (ProjectileType)
	{
	case SpawnedByPlayer:
		{
			auto Enemy = Cast<AIGEnemyBase>(Result.GetActor());
			if (!Enemy)
			{
				return;
			}
			UE_LOG(LogTemp, Log, TEXT("적에 닿음"));

			FDamageEvent DamageEvent;
			Enemy->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
			break;
		}
	case SpawnedByEnemy:
		{
			auto Player = Cast<AIGPlayerCharacter>(Result.GetActor());
			if (!Player)
			{
				return;
			}
			UE_LOG(LogTemp, Log, TEXT("플레이어에 닿음"));

			FDamageEvent DamageEvent;
			Player->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
			break;
		}
	default:
		checkNoEntry();
		break;
	}

	UE_LOG(LogTemp, Log, TEXT("투사체 파괴"));
	OnHitProjectile.Broadcast();
	Destroy();
}
