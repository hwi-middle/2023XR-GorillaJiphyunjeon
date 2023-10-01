// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGOldTree.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Management/IGBossZoneGateManager.h"

// Sets default values
AIGOldTree::AIGOldTree()
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
void AIGOldTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGOldTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGOldTree::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("결정을 다 찾지 못해도 이 나무를 통해 문을 열 수 있어!")));
	IGBossZoneGateManager::GetInstance()->OpenGate();
}

