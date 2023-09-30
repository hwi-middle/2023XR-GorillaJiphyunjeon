// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class IIGCrystalInterface;
class IGPlayerInventory;

class AIGWaveCrystal;
class AIGTreeCrystal;
class AIGMountainCrystal;

class INDIGO_API IGCrystalManager
{
public:

	
	IGCrystalManager();
	~IGCrystalManager();

public:
	static TSharedPtr<IGCrystalManager> GetInstance();
	
	void ActivitedCrystal(IIGCrystalInterface* InCrystal);

	
private:
	IGPlayerInventory* PlayerInventory;
};
