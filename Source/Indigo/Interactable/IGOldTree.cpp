// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGOldTree.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoOldTreePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/Management/IGBossZoneGateManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGOldTree::AIGOldTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/Tree/SM_tree_04.SM_tree_04'"), [&](UStaticMesh* MeshRef)
{
Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
Mesh->SetStaticMesh(MeshRef);
Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
RootComponent = Mesh;
Mesh->SetCollisionProfileName(TEXT("Evidence"));
}, EAssertionLevel::None);	
}

// Called when the game starts or when spawned
void AIGOldTree::BeginPlay()
{
	Super::BeginPlay();

	AIGProvisoOldTreePlace* LocalActor = GetWorld()->SpawnActor<AIGProvisoOldTreePlace>(AIGProvisoOldTreePlace::StaticClass(), GetActorLocation(), GetActorRotation());
	LocalActor->SetActorScale3D(GetActorScale()*5);
	
}

// Called every frame
void AIGOldTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGOldTree::Interact()
{
	APawn* PlayerController = UGameplayStatics::GetPlayerPawn(GWorld, 0);
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerController);

	if(IGPlayerCharacter == nullptr)
	{
		return;
	}

	if((IGPlayerCharacter->GetInventory()->GetMountainCrystalArray().Num() +
		IGPlayerCharacter->GetInventory()->GetTreeCrystalArray().Num() +
		IGPlayerCharacter->GetInventory()->GetWaveCrystalArray().Num()) < 9)
	{
		IGPlayerCharacter->GetShinmyophil()->ProvisoRemakeNoFindCrystalAndInteractToOldTree();
		IGBossZoneGateManager::GetInstance()->OpenGate();
	}
	
	
}

