// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMoutainCrystal.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Util/IGScriptDataTable.h"

// Sets default values
AIGMoutainCrystal::AIGMoutainCrystal()
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

	FIGDataTableParser::LoadAndInitializeDataTable(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/ProvisoStoryScript.ProvisoStoryScript'"),
		[&](const UDataTable* ScriptDataTable)
		{			
			MountainCrystalScript = ScriptDataTable->FindRow<FIGScriptDataTable>(TEXT("바위산"),TEXT(""));			
		});
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s]"), *MountainCrystalScript->Name));
	
}

// Called when the game starts or when spawned
void AIGMoutainCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGMoutainCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGMoutainCrystal::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s]"), *MountainCrystalScript->Script));
}

