// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPhasePlaceBase.h"
#include "Components/BoxComponent.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Character/IGPlayerCharacter.h"

// Sets default values
AIGPhasePlaceBase::AIGPhasePlaceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	PlayerCharacter = nullptr;
}

AIGPhasePlaceBase::~AIGPhasePlaceBase()
{
	
}

// Called when the game starts or when spawned
void AIGPhasePlaceBase::BeginPlay()
{
	Super::BeginPlay();
}

void AIGPhasePlaceBase::EnterPhasePlace()
{
	if(PlayerCharacter == nullptr)
	{
		return;
	}
}

// Called every frame
void AIGPhasePlaceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugBox(GetWorld(), GetActorLocation(), BoxCollider->GetScaledBoxExtent(), FColor::Green, false, 1.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeBox(BoxCollider->GetScaledBoxExtent()),
		CollisionParams
	);

	if (!bHit)
	{
		return;
	}

	PlayerCharacter = Cast<AIGPlayerCharacter>(Result.GetActor());
	if (PlayerCharacter != nullptr)
	{
		EnterPhasePlace();		
	}

}

