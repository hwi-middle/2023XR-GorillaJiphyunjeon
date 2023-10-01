// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossZoneGateManager.h"
TSharedPtr<IGBossZoneGateManager> Instance = MakeShareable(new IGBossZoneGateManager());
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

	return Instance;
}
