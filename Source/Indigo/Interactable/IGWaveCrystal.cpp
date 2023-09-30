// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveCrystal.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Management/IGCrystalManager.h"

TSharedPtr<IGCrystalManager> Instance = IGCrystalManager::GetInstance();

// Sets default values
AIGWaveCrystal::AIGWaveCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsGetCrystal = false;
	
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
			WaveCrystalScript = ScriptDataTable->FindRow<FIGScriptDataTable>(TEXT("파도"),TEXT(""));			
		});
	Instance = IGCrystalManager::GetInstance();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s]"), *WaveCrystalScript->Name));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%p]"), Instance.Get()->GetInstance().Get()));

}

// Called when the game starts or when spawned
void AIGWaveCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGWaveCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGWaveCrystal::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s]"), *WaveCrystalScript->Script));
	TakeCrystal();
}

void AIGWaveCrystal::TakeCrystal()
{
	if(bIsGetCrystal == true)
	{
		return;		
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("[%s]의 결정 습득"), *WaveCrystalScript->Name));

	if(Instance.IsValid())
	{
		Instance.Get()->ActivitedCrystal(this);
	}
	bIsGetCrystal = true;
	Destroy();
}