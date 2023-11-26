// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerInventory.h"

#include "IGShinmyophil.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interactable/IGMountainCrystal.h"
#include "Indigo/Interactable/IGWaveCrystal.h"
#include "Indigo/Interactable/IGTreeCrystal.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Interactable/IGMainHint.h"
#include "Indigo/Management/IGBossZoneGateManager.h"
#include "Indigo/CommonMonsters/ASector/IGMountainSectorMonster.h"
#include "Indigo/CommonMonsters/ASector/IGWaveSectorMonster.h"
#include "Indigo/CommonMonsters/ASector/IGPineTreeSectorMonster.h"
#include "Kismet/GameplayStatics.h"


UIGPlayerInventory::UIGPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsGetFirstCrystal = false;
	bIsGetFirstBlankHint = false;
	bIsGetFirstHint = false;
	bIsGet2HintBySameProviso =false;
	bIsGetFirstCrystal = false;
	CantFindProvisoTime = 0.0f;
}

UIGPlayerInventory::~UIGPlayerInventory()
{}

void UIGPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

}

void UIGPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AIGPlayerCharacter* PlayerCharacter = Cast<AIGPlayerCharacter>(GetOwner());
	if(PlayerCharacter == nullptr)
	{
		return;
	}
	if(PlayerCharacter->GetShinmyophil()->GetCurrentPhaseState() == EPhaseState::ProvisoPhase
		&& MountainCrystalArray.Num() <= 0
		&& WaveCrystalArray.Num() <= 0
		&& TreeCrystalArray.Num() <= 0)
	{	
		CantFindProvisoTime+=DeltaTime;
	}
	if(CantFindProvisoTime >= 180.0f)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoRemakeCantFindCrystalAnd3Minute();
		CantFindProvisoTime = 0.0f;
	}

}

void UIGPlayerInventory::AddCrystal(ECrystal InCrystalType)
{
	switch(InCrystalType)
	{
	case ECrystal::Mountain:
		MountainCrystalArray.Add(NewObject<AIGMountainCrystal>());
		break;		

	case ECrystal::Tree:
		TreeCrystalArray.Add(NewObject<AIGTreeCrystal>());	
		break;

	case ECrystal::Wave:
		WaveCrystalArray.Add(NewObject<AIGWaveCrystal>());	
		break;
		
		default:
			break;
	}
	
	
	const AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(GetOwner());	
	if(Player == nullptr)
	{
		return;
	}
	
	if(!bIsGetFirstCrystalFrag)
	{
		//처음 결정 조각 얻었을 떄
		Player->GetShinmyophil()->ProvisoRemakeFirstGetCrystalFrag();
		bIsGetFirstCrystalFrag = true;
	}
	
	if(!bIsGetFirstCrystal)
	{
		if(MountainCrystalArray.Num() >= 3 || TreeCrystalArray.Num() >= 3 || WaveCrystalArray.Num() >= 3)
		{
			//3개 모아서 결정 하나 만들었을 떄
			Player->GetShinmyophil()->ProvisoRemakeGetAllCrystalAndGetCompleteCrystal();
			bIsGetFirstCrystal = true;		
		}
	}


	//각 구역 결정 먹었을 때 필드 위 몹 제거	
	if (MountainCrystalArray.Num() >= 3)
	{
		TArray<AActor*> Wisps;
		UGameplayStatics::GetAllActorsOfClass(GWorld, AIGMountainSectorMonster::StaticClass(), Wisps);
		for (AActor* Actor : Wisps)
		{
			Actor->Destroy();
		}
	}
	if (TreeCrystalArray.Num() >= 3)
	{
		TArray<AActor*> Wisps;
		UGameplayStatics::GetAllActorsOfClass(GWorld, AIGPineTreeSectorMonster::StaticClass(), Wisps);
		for (AActor* Actor : Wisps)
		{
			Actor->Destroy();
		}
	}
	if (WaveCrystalArray.Num() >= 3)
	{
		TArray<AActor*> Wisps;
		UGameplayStatics::GetAllActorsOfClass(GWorld, AIGWaveSectorMonster::StaticClass(), Wisps);
		for (AActor* Actor : Wisps)
		{
			Actor->Destroy();
		}
	}
			
	if (MountainCrystalArray.Num() >= 3 &&
		TreeCrystalArray.Num() >= 3 &&
		WaveCrystalArray.Num() >= 3
		)
	{
		//다 모았을 때
		//IGBossZoneGateManager::GetInstance()->OpenGate();
		Player->GetShinmyophil()->ProvisoRemakeGetAllCrystal();
	}
}

void UIGPlayerInventory::AddHint(ProvisoText* InHint)
{
	for(const ProvisoText* Hint : HintArray)
	{
		if(Hint->HintType == InHint->HintType && InHint->HintType != EHintType::Blank)
		{
			Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGet2HintToSameProviso();					
		}	
	}
	
	HintArray.AddUnique(InHint);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Hints Name: [%s]"), *InHint->Name));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("힌트 갯수: [%d]"), HintArray.Num()));

	if(bIsGetFirstHint == false && InHint->HintType != EHintType::Blank)
	{ 
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetFirstHint();
		bIsGetFirstHint = true;
	}
	if(bIsGetFirstBlankHint == false && InHint->HintType == EHintType::Blank)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetFirstBlankHint();
		bIsGetFirstBlankHint = true;
	}
	
	int32 MainHintCount = 0;
	for(const ProvisoText* Hint : HintArray)
	{
		if(Hint->HintType != EHintType::Blank)
		{
			MainHintCount++;
		}
	}	
	
	if(MainHintCount >= 6)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetHint6All();
	}	
}

