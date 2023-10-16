// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintBase.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGTextMasterDataTable.h"
#include "Indigo/Util/IGDataTableParser.h"

AIGHintBase::AIGHintBase()
{
Path = TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/TextMasterDataTable/Text_Master.Text_Master'");
	
	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("Evidence"));
}, EAssertionLevel::Check);

	FIGDataTableParser::LoadAndInitializeDataTable(*Path,
		[&](const UDataTable* ScriptDataTable)
		{
			TArray<FIGTextMasterDataTable*> ScriptArray;
			ScriptDataTable->GetAllRows(TEXT(""), ScriptArray);


			for(int32 i = 0;  i < ScriptArray.Num(); i++)
			{
				if(ScriptArray[i]->TextMain == 1 && ScriptArray[i]->TextSub == 1)
				{
					HintTextTitleArray.AddUnique(ScriptArray[i]);
				}
				if(ScriptArray[i]->TextMain == 1 && ScriptArray[i]->TextSub == 2)
				{
					HintTextScriptArray.AddUnique(ScriptArray[i]);
				}
			}

			for(int32 i = 0; i < HintTextTitleArray.Num(); i++)
			{
				ProvisoText* HintTextScript = new ProvisoText();
				HintTextScript->Name = HintTextTitleArray[i]->Text;
				HintTextScript->Script = HintTextScriptArray[i]->Text;
				HintScriptArray.AddUnique(HintTextScript);
			}
			
		});

	
	
}

AIGHintBase::~AIGHintBase()
{
}

void AIGHintBase::InitHintType(const EHintType InHintType)
{
	CurrentHintType = InHintType;

	//Temporal
	if(CurrentHintType == EHintType::Mountain)
	{
		HintScript = HintScriptArray[FMath::RandRange(0,1)];
	}
	if(CurrentHintType == EHintType::Wave)
	{
		HintScript = HintScriptArray[FMath::RandRange(2, 3)];		
	}
	if(CurrentHintType == EHintType::PineTree)
	{
		HintScript = HintScriptArray[FMath::RandRange(4,5)];				
	}	
	if(CurrentHintType == EHintType::Blanc)
	{
		HintScript = HintScriptArray[FMath::RandRange(6,8)];				
	}	
}


void AIGHintBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("[%s]"), *HintScript->Script));
}
