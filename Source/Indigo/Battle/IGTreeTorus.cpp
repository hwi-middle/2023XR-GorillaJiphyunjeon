// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTreeTorus.h"

#include "Engine/DamageEvents.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGTreeTorus::AIGTreeTorus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorusMesh"));
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleBossAttack/TreeAttack/Mesh/SM_TreeAttack.SM_TreeAttack'"), [&](UStaticMesh* MeshRef)
	{
		Mesh->SetStaticMesh(MeshRef);
		RootComponent = Mesh;
	}, EAssertionLevel::Check);

	CurrentScale = 0.f;

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
}

// Called when the game starts or when spawned
void AIGTreeTorus::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIGTreeTorus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsInitialized)
	{
		return;
	}

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= Duration)
	{
		Destroy();
		return;
	}

	CurrentScale += ScaleFactorPerSecond * DeltaTime;
	Mesh->SetWorldScale3D(FVector(CurrentScale));

	if (bHasDamagedPlayer)
	{
		return;
	}

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	constexpr float Radius = 100.f;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius * CurrentScale, 16, FColor::Green, false, 0.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(Radius * CurrentScale),
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
		Player->TakeDamage(10.f, DamageEvent, GetInstigatorController(), this);
		bHasDamagedPlayer = true;
	}
}

void AIGTreeTorus::Init(const float InScaleFactor, const float InDuration)
{
	ScaleFactorPerSecond = InScaleFactor;
	Duration = InDuration;
	bIsInitialized = true;
}
