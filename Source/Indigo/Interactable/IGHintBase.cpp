// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintBase.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Util/IGScriptDataTable.h"

AIGHintBase::AIGHintBase()
{
}

AIGHintBase::AIGHintBase(FString InPath)
	:Path(InPath)
{
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("Evidence"));
}, EAssertionLevel::Check);

	static uint8 ScriptNum = 1;
	FIGDataTableParser::LoadAndInitializeDataTable(*Path,
		[&](const UDataTable* ScriptDataTable)
		{
			TArray<FIGScriptDataTable*> ScriptArray;
			
			HintScript = ScriptDataTable->FindRow<FIGScriptDataTable>(FName(*(FString::FormatAsNumber(ScriptNum))),TEXT(""));

			ScriptNum++;
			if (ScriptArray.Num() < ScriptNum)
			{
				ScriptNum = 1;
			}
			
		});
}

AIGHintBase::~AIGHintBase()
{
}


void AIGHintBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("[%s]"), *HintScript->Script));
}
