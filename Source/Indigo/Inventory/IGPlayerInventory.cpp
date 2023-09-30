// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerInventory.h"

IGPlayerInventory::IGPlayerInventory()
{
	
}

IGPlayerInventory::~IGPlayerInventory()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%d]개"), ArrCrystals.Num()));
		
}

void IGPlayerInventory::AddCrystals(IIGCrystalInterface* InCrystal)
{
	if(InCrystal == nullptr)
	{
		return;
	}
	
	if(ArrCrystals.Num() > 0 && ArrCrystals.Num() < 3)
	{		
		for(const IIGCrystalInterface* Crystals : ArrCrystals)
		{	
			if(InCrystal->GetCrystalName() == Crystals->GetCrystalName())
			{
				return;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%d]"), ArrCrystals.Num()));
	ArrCrystals.Add(InCrystal);
	ShowMyCrystals();
}

void IGPlayerInventory::ShowMyCrystals()
{
	for(const IIGCrystalInterface* Crystals: ArrCrystals)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]의 결정 소유"), *Crystals->GetCrystalName()));
	}
}
