// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Interface/IGCrystalInterface.h"
/**
 * 
 */

class AIGWaveCrystal;
class AIGTreeCrystal;
class AIGMountainCrystal;

class INDIGO_API IGPlayerInventory 
{
public:
	IGPlayerInventory();
	~IGPlayerInventory();

	void AddCrystals(IIGCrystalInterface* InCrystal);
	void ShowMyCrystals();

	FORCEINLINE TArray<IIGCrystalInterface*> GetArrCrystals(){return ArrCrystals;}
	
private:
	TArray<IIGCrystalInterface*> ArrCrystals;
	
};
