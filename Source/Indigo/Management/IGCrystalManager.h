// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */

constexpr uint8 STAGE_CRYSTALS = 3;

class IIGCrystalInterface;

class INDIGO_API IGCrystalManager 
{
public:	
	IGCrystalManager();
	~IGCrystalManager();

	static TSharedPtr<IGCrystalManager> GetInstance();
	
	void OnFoundAllCrystals();
	

};
