// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrystalBase.h"
#include "Indigo/Management/IGCrystalManager.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoWispPlace.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"

// Sets default values
AIGCrystalBase::AIGCrystalBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AIGCrystalBase::AIGCrystalBase(FString InPath, FName InName)
{
	bIsTaken = false;


	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		Mesh->SetStaticMesh(MeshRef);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		RootComponent = Mesh;
		Mesh->SetCollisionProfileName(TEXT("Evidence"));
	}, EAssertionLevel::Check);

	FIGDataTableParser::LoadAndInitializeDataTable(*InPath, [&](const UDataTable* ScriptDataTable)
	{
		CrystalScript = ScriptDataTable->FindRow<FIGScriptDataTable>(InName,TEXT(""));
	});
}

// Called when the game starts or when spawned
void AIGCrystalBase::BeginPlay()
{
	Super::BeginPlay();

	AIGProvisoWispPlace* LocalActor = GetWorld()->SpawnActor<AIGProvisoWispPlace>(AIGProvisoWispPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	LocalActor->SetActorScale3D(GetActorScale() * 5);
	
}

// Called every frame
void AIGCrystalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGCrystalBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]"), *CrystalScript->Script));
	Take();
}

void AIGCrystalBase::Take()
{
	if (bIsTaken)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("[%s]의 결정 습득"), *CrystalScript->Name));

	bIsTaken = true;

	Destroy();
}
