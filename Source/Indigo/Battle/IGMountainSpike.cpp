// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainSpike.h"

#include "Engine/DamageEvents.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGMountainSpike::AIGMountainSpike()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpiikeMesh"));
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleBossAttack/MountainAttack/Mesh/SM_MountainAttack.SM_MountainAttack'"), [&](UStaticMesh* MeshRef)
	{
		Mesh->SetStaticMesh(MeshRef);
	}, EAssertionLevel::Check);

	ElapsedTime = 0.f;
	bIsInitialized = false;
	bHasDamagedPlayer = false;
}

// Called when the game starts or when spawned
void AIGMountainSpike::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIGMountainSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsInitialized)
	{
		return;
	}

	ElapsedTime += DeltaTime;
	if (ElapsedTime < GenerationDelay)
	{
		return;
	}

	// 최종 삭제
	if (ElapsedTime - GenerationDelay > Duration + DestroyDelay)
	{
		Destroy();
	}

	const float Alpha = FMath::Clamp((ElapsedTime - GenerationDelay) / Duration, 0.f, 1.f);
	SetActorLocation(FMath::Lerp(OriginPos, TargetPos, Alpha));

	// 플레이어 타격은 등장 중에만 진행
	if (ElapsedTime - GenerationDelay > Duration)
	{
		return;
	}
	
	if (bHasDamagedPlayer)
	{
		return;
	}

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float DamageRadius = 150.f;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 16, FColor::Green, false, 1.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(DamageRadius),
		CollisionParams
	);

	if (!bHit)
	{
		return;
	}

	AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor());
	if (Player)
	{
		FDamageEvent DamageEvent;
		Player->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
		bHasDamagedPlayer = true;
	}
}

void AIGMountainSpike::Init(const float InDamage, const float InHeight, const float InGenerationDelay, const float InDuration, const float InDestroyDelay)
{
	OriginPos = GetActorLocation();
	Damage = InDamage;
	TargetPos = OriginPos + FVector(0.f, 0.f, InHeight);
	GenerationDelay = InGenerationDelay;
	Duration = InDuration;
	DestroyDelay = InDestroyDelay;
	bIsInitialized = true;
}
