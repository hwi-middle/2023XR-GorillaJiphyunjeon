// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGEvidence.h"

#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGEvidence::AIGEvidence()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		Mesh->SetStaticMesh(MeshRef);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		RootComponent = Mesh;
		Mesh->SetCollisionProfileName(TEXT("Evidence"));
	}, EAssertionLevel::Check);
}

// Called when the game starts or when spawned
void AIGEvidence::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIGEvidence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGEvidence::Interact()
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s] 단서 상호작용"), *GetActorLabel()));
}
