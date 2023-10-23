// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProjectileBase.h"

#include "Engine/DamageEvents.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGProjectileBase::AIGProjectileBase()
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

// Called when the game starts or when spawned
void AIGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ElapsedTime = 0;
}

// Called every frame
void AIGProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime > Duration)
	{
		Destroy();
	}

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
	
	switch (SpawnType)
	{
	case SpawnedByPlayer:
		{
			auto Enemy = Cast<AIGEnemyBase>(Result.GetActor());
			if (!Enemy)
			{
				return;
			}

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

			FDamageEvent DamageEvent;
			Player->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
			break;
		}
	default:
		checkNoEntry();
		break;
	}

	OnHitProjectile.Broadcast();
	Destroy();
}
