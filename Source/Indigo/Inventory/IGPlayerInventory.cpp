// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerInventory.h"
#include "Indigo/Management/IGCrystalManager.h"


UIGPlayerInventory::UIGPlayerInventory()
{
}
UIGPlayerInventory::~UIGPlayerInventory()
{		
}

void UIGPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void UIGPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UIGPlayerInventory::AddCrystals(IIGCrystalInterface* InCrystal)
{	
	ArrCrystals.AddUnique(InCrystal);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("현재 결정 갯수: [%d]"), ArrCrystals.Num()));	
	ShowMyCrystals();

	if(ArrCrystals.Num() >= 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("결정을 다 찾았어!")));
		IGCrystalManager::GetInstance()->FoundAllCrystals();		
	}
	
}

void UIGPlayerInventory::ShowMyCrystals()
{
	for(const IIGCrystalInterface* Crystals: ArrCrystals)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]의 결정 소유"), *Crystals->GetCrystalName()));
	}
}

void UIGPlayerInventory::AddHints(IIGHintInterface* InHint)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%d]"), ArrHints.Num()));
	ArrHints.AddUnique(InHint);	
}
