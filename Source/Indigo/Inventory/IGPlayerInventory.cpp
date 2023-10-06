// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerInventory.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Management/IGCrystalManager.h"


UIGPlayerInventory::UIGPlayerInventory()
{}

UIGPlayerInventory::~UIGPlayerInventory()
{}

void UIGPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

}

void UIGPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UIGPlayerInventory::AddCrystal(AIGCrystalBase* InCrystal)
{
	CrystalArray.AddUnique(InCrystal);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("현재 결정 갯수: [%d]"), CrystalArray.Num()));
	ShowOwnedCrystals();

	if (CrystalArray.Num() >= 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("결정을 다 찾았어!")));
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

void UIGPlayerInventory::AddHint(IIGHintInterface* InHint)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%d]"), HintArray.Num()));
	HintArray.AddUnique(InHint);
}
