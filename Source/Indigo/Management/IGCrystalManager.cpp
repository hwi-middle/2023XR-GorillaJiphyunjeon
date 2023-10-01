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
	TSharedPtr<IGCrystalManager> Instance = MakeShareable(new IGCrystalManager());
	return Instance;
}

void IGCrystalManager::FoundAllCrystals()
{
	IGBossZoneGateManager::GetInstance()->OpenGate();
}

void IGCrystalManager::FoundCrystal()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("남은 결정 수 [%d]개"), STAGE_CRYSTALS));
}


