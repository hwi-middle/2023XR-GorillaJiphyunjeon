// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProjectile.h"

#include "Engine/DamageEvents.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Character/IGEnemyBase.h"
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

void AIGProjectile::Init(float InDamage, FVector InTargetDirection, float MaxDistance, float InSpeed)
{
	Damage = InDamage;
	OriginalPosition = GetActorLocation();
	TargetPosition = OriginalPosition + InTargetDirection * MaxDistance;

	const float DistancePerSecond = InSpeed * 100.f;
	const float DistanceToTarget = (TargetPosition - OriginalPosition).Size2D();
	Duration = DistanceToTarget / DistancePerSecond;
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
	CollisionParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);	

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_PROJECTILE,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (!bHit)
	{
		return;
	}

	auto Enemy = Cast<AIGEnemyBase>(Result.GetActor());
	if (Enemy)
	{
		FDamageEvent DamageEvent;
		Enemy->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
		OnHitProjectile.Broadcast();
	}

	Destroy();
}
