// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBlankHint.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Util/IGScriptDataTable.h"

// Sets default values
AIGBlankHint::AIGBlankHint()
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

	static uint8 ScriptNum = 1;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%d]"), ScriptNum));
	FIGDataTableParser::LoadAndInitializeDataTable(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/BlankHintScript.BlankHintScript'"),
		[&](const UDataTable* ScriptDataTable)
		{
			TArray<FIGScriptDataTable*> ScriptArray;
			ScriptDataTable->GetAllRows(TEXT(""), ScriptArray);
			
			BlankHintScript = ScriptDataTable->FindRow<FIGScriptDataTable>(FName(*(FString::FormatAsNumber(ScriptNum))),TEXT(""));

			ScriptNum++;
			if(ScriptArray.Num() < ScriptNum)
			{
				ScriptNum = 1;
				return;
			}
			
		});
}

// Called when the game starts or when spawned
void AIGBlankHint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGBlankHint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGBlankHint::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("[%s]"), *BlankHintScript->Script));
}