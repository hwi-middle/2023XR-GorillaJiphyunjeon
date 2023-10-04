// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrystalParent.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Management/IGCrystalManager.h"

// Sets default values
AIGCrystalParent::AIGCrystalParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AIGCrystalParent::AIGCrystalParent(FString InPath, FName InName)
{
	bIsGetCrystal = false;
	
	
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
{
Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
Mesh->SetStaticMesh(MeshRef);
Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
RootComponent = Mesh;
Mesh->SetCollisionProfileName(TEXT("Evidence"));
}, EAssertionLevel::Check);

	FIGDataTableParser::LoadAndInitializeDataTable(*InPath,
		[&](const UDataTable* ScriptDataTable)
		{
			CrystalScript = ScriptDataTable->FindRow<FIGScriptDataTable>(InName,TEXT(""));			
		});
}

// Called when the game starts or when spawned
void AIGCrystalParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGCrystalParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGCrystalParent::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]"), *CrystalScript->Script));
	TakeCrystal();
}

void AIGCrystalParent::TakeCrystal()
{
	if(bIsGetCrystal == true)
	{
		return;		
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("[%s]의 결정 습득"), *CrystalScript->Name));

	bIsGetCrystal = true;
}

