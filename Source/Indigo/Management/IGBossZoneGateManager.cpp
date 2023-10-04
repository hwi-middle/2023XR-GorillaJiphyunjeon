// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossZoneGateManager.h"

IGBossZoneGateManager::IGBossZoneGateManager()
{
	
}

IGBossZoneGateManager::~IGBossZoneGateManager()
{
	
}

void IGBossZoneGateManager::OpenGate()
{
	if(FOpenGateDelegate.IsBound() == true)
	{
		FOpenGateDelegate.Execute();		
	}
}

TSharedPtr<IGBossZoneGateManager> IGBossZoneGateManager::GetInstance()
{
	static TSharedPtr<IGBossZoneGateManager> Instance = MakeShareable(new IGBossZoneGateManager());
	return Instance;
}
