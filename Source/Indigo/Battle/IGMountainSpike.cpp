// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainSpike.h"

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

	// UE_LOG(LogTemp, Log, TEXT("DeltaTime: %f, Elapsed: %f, Duration: %f"), DeltaTime, ElapsedTime, Duration);
	if (ElapsedTime > Duration + DestroyDelay)
	{
		Destroy();
	}

	const float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);
	SetActorLocation(FMath::Lerp(OriginPos, TargetPos, Alpha));
}

void AIGMountainSpike::Init(const float InHeight, const float InDuration, const float InDestroyDelay)
{
	OriginPos = GetActorLocation();
	TargetPos = OriginPos + FVector(0.f, 0.f, InHeight);
	UE_LOG(LogTemp, Log, TEXT("%f"), TargetPos.Z);
	Duration = InDuration;
	DestroyDelay = InDestroyDelay;

	bIsInitialized = true;
}
