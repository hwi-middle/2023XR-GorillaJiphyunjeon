// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrystalManager.h"
#include "Indigo/Management/IGBossZoneGateManager.h"


IGCrystalManager::IGCrystalManager()
{
}


IGCrystalManager::~IGCrystalManager()
{
	
}

TSharedPtr<IGCrystalManager> IGCrystalManager::GetInstance()
{
	static TSharedPtr<IGCrystalManager> Instance = MakeShareable(new IGCrystalManager());
	return Instance;
}

void IGCrystalManager::OnFoundAllCrystals()
{
	IGBossZoneGateManager::GetInstance()->OpenGate();
}


