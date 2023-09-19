// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Evidence.h"

#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AEvidence::AEvidence()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		Mesh->SetStaticMesh(MeshRef);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		RootComponent = Mesh;
	}, EAssertionLevel::Check);
}

// Called when the game starts or when spawned
void AEvidence::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEvidence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEvidence::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("단서 상호작용"));
}
