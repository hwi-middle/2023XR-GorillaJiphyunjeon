// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerInventory.h"

#include "IGShinmyophil.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Management/IGCrystalManager.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Interactable/IGBlankHint.h"
#include "Indigo/Interactable/IGMainHint.h"


UIGPlayerInventory::UIGPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsGetFirstCrystal = false;
	bIsGetFirstBlancHint = false;
	bIsGetFirstHint = false;
	bIsGet2HintBySameProviso =false;
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
	if(PlayerCharacter->GetShinmyophil()->GetCurrentPhaseState() == EPhaseState::ProvisoPhase)
	{	
		CantFindProvisoTime+=DeltaTime;
	}
	if(CantFindProvisoTime >= 180.0f)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoNotFindAllProvisoAndSkip3Minute();
		CantFindProvisoTime = 0.0f;
	}

}

void UIGPlayerInventory::AddCrystal(AIGCrystalBase* InCrystal)
{
	CrystalArray.AddUnique(InCrystal);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("현재 결정 갯수: [%d]"), CrystalArray.Num()));
	ShowOwnedCrystals();

	if(bIsGetFirstCrystal == false)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetFirstProviso();
		bIsGetFirstCrystal = true;
	}
	
	if (CrystalArray.Num() >= 3)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetAllProviso();
		IGCrystalManager::GetInstance()->OnFoundAllCrystals();
	}
}

void UIGPlayerInventory::ShowOwnedCrystals()
{
	for (const AIGCrystalBase* Crystals : CrystalArray)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]의 결정 소유"), *Crystals->GetCrystalName()));
	}
}

void UIGPlayerInventory::AddHint(ProvisoText* InHint)
{
	for(const ProvisoText* Hint : HintArray)
	{
		if(Hint->Name == InHint->Name && InHint->Name == "")
		{
			return;
		}		
	}
	if(InHint->HintType == EHintType::Blanc)
	{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("BlankHint")));
		
	}
	
	HintArray.AddUnique(InHint);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Hints Name: [%s]"), *InHint->Name));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("힌트 갯수: [%d]"), HintArray.Num()));

	if(bIsGetFirstHint == false && InHint->HintType != EHintType::Blanc)
	{ 
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetFirstHint();
		bIsGetFirstHint = true;
	}
	if(bIsGetFirstBlancHint == false && InHint->HintType == EHintType::Blanc)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetFirstBlancHint();
		bIsGetFirstBlancHint = true;
	}
	
	int32 MainHintCount = 0;
	for(const ProvisoText* Hint : HintArray)
	{
		if(Hint->HintType != EHintType::Blanc)
		{
			MainHintCount++;
		}
	}
	for(int i =0; i < HintArray.Num(); i++)
	{
		for(int j = i+1; j < HintArray.Num(); j++)
		{
			if(HintArray[i]->HintType == HintArray[j]->HintType && HintArray[i]->HintType != EHintType::Blanc && HintArray[i]->Name != HintArray[j]->Name)
			{
				Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGet2HintToSameProviso();			
			}
		}
	}
	
	
	if(MainHintCount >= 6)
	{
		Cast<AIGPlayerCharacter>(GetOwner())->GetShinmyophil()->ProvisoGetHint6All();
	}	
}

