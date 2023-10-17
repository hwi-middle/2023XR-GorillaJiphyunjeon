// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintBase.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGTextMasterDataTable.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Kismet/GameplayStatics.h"

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

				if(i < 2)
				{
					MountainHintScriptArray.AddUnique(HintTextScript);
				}
				else if(i > 1 && i < 4)
				{
					WaveHintScriptArray.AddUnique(HintTextScript);
				}
				else if(i > 3 && i < 6)
				{
					PineTreeHintScriptArray.AddUnique(HintTextScript);
				}
				else if(i > 6)
				{
					BlankHintScriptArray.AddUnique(HintTextScript);
				}
				HintScriptArray.AddUnique(HintTextScript);
				
			}			
		});
}

AIGHintBase::~AIGHintBase()
{
}

void AIGHintBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void AIGHintBase::InitHintType(const EHintType InHintType)
{

	
	
	HintScript = new ProvisoText();
	HintScript->HintType = InHintType;

	if((HintScript->HintType == EHintType::Mountain && MountainHintScriptArray.Num() <= 0) ||
		(HintScript->HintType == EHintType::Wave && WaveHintScriptArray.Num() <= 0) ||
		(HintScript->HintType == EHintType::PineTree && PineTreeHintScriptArray.Num() <= 0))
	{
		HintScript->HintType = EHintType::Blanc;
	}
	if( InHintType == EHintType::Blanc && BlankHintScriptArray.Num() <= 0)
	{
		Destroy();
		return;
	}
	
	const AIGPlayerCharacter* PlayerCharacter = Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0));
	if(HintScript->HintType == EHintType::Mountain && MountainHintScriptArray.Num() > 0)
	{
		const int32 RandomNumber = FMath::RandRange(0,MountainHintScriptArray.Num()-1);
		HintScript = MountainHintScriptArray[RandomNumber];

		if(PlayerCharacter != nullptr && PlayerCharacter->GetInventory()->GetHintArray().Num() > 0)
		{
			for(const ProvisoText* Hint : PlayerCharacter->GetInventory()->GetHintArray())
			{
				if(Hint->Name == HintScript->Name)
				{
					MountainHintScriptArray.RemoveAt(RandomNumber);
					InitHintType(InHintType);
					break;
				}
			}
		}		
	}
	if(HintScript->HintType == EHintType::Wave && WaveHintScriptArray.Num() > 0)
	{
		const int32 RandomNumber = FMath::RandRange(0,WaveHintScriptArray.Num()-1);
		HintScript = WaveHintScriptArray[RandomNumber];

		if(PlayerCharacter != nullptr && PlayerCharacter->GetInventory()->GetHintArray().Num() > 0)
		{
			for(const ProvisoText* Hint : PlayerCharacter->GetInventory()->GetHintArray())
			{
				if(Hint->Name == HintScript->Name)
				{
					WaveHintScriptArray.RemoveAt(RandomNumber);
					InitHintType(InHintType);
					break;
				}
			}
		}
	}
	if(HintScript->HintType == EHintType::PineTree && PineTreeHintScriptArray.Num() > 0)
	{
		const int32 RandomNumber = FMath::RandRange(0,PineTreeHintScriptArray.Num()-1);
		HintScript = PineTreeHintScriptArray[RandomNumber];

		if(PlayerCharacter != nullptr && PlayerCharacter->GetInventory()->GetHintArray().Num() > 0)
		{
			for(const ProvisoText* Hint : PlayerCharacter->GetInventory()->GetHintArray())
			{
				if(Hint->Name == HintScript->Name)
				{
					PineTreeHintScriptArray.RemoveAt(RandomNumber);
					InitHintType(InHintType);
					break;
				}
			}
		}
	}	
	if(HintScript->HintType == EHintType::Blanc && BlankHintScriptArray.Num() > 0)
	{
		const int32 RandomNumber = FMath::RandRange(0,BlankHintScriptArray.Num()-1);
		HintScript = BlankHintScriptArray[RandomNumber];

		if(PlayerCharacter != nullptr && PlayerCharacter->GetInventory()->GetHintArray().Num() > 0)
		{
			for(const ProvisoText* Hint : PlayerCharacter->GetInventory()->GetHintArray())
			{
				if(Hint->Name == HintScript->Name)
				{
					BlankHintScriptArray.RemoveAt(RandomNumber);
					InitHintType(InHintType);
					break;
				}
			}
		}
	}


	TArray<AActor*> DropHintArray;
	UGameplayStatics::GetAllActorsOfClass(GWorld, AIGHintBase::StaticClass(), DropHintArray);
	for(AActor* Hint : DropHintArray)
	{
		if(Cast<AIGHintBase>(Hint) != nullptr && DropHintArray.Num() > 0)
		{
			if(Cast<AIGHintBase>(Hint)->GetHintName() == GetHintName() && Cast<AIGHintBase>(Hint) != this)
			{
				Destroy();
				return;
			}
		}	
	}


	
}


void AIGHintBase::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("[Name:  %s]"), *HintScript->Name));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("[Desc: %s]"), *HintScript->Script));
	Destroy();
}

void AIGHintBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
}
