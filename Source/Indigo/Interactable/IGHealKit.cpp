// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/Interactable/IGHealKit.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGHealKit::AIGHealKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = Mesh;
}, EAssertionLevel::Check);
	
}

// Called when the game starts or when spawned
void AIGHealKit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGHealKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 100.f;

	TArray<AActor*> IgnoredWisps;
	TArray<AActor*> IgnoredHealKits;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIGHintMonsterBase::StaticClass(), IgnoredWisps);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), IgnoredHealKits);

	for (AActor* Wisps : IgnoredWisps)
	{
		CollisionParams.AddIgnoredActor(Wisps);
	}
	for (AActor* HealKits : IgnoredHealKits)
	{
		CollisionParams.AddIgnoredActor(HealKits);
	}

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);

	if (!bHit)
	{
		return;
	}

	if (AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor()))
	{
		Player->AddHealKit();
		Destroy();
	}
	

}

