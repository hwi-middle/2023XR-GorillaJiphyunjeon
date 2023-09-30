// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProjectile.h"

#include "Indigo/Util/IGConstructorHelper.h"

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
	if(ElapsedTime > Duration)
	{
		Destroy(this);
	}
	
	float Alpha = ElapsedTime / Duration;
	SetActorLocation(FMath::Lerp(OriginalPosition, TargetPosition, Alpha));
}

