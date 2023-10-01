// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE(FOpenGate_Dele)

class INDIGO_API IGBossZoneGateManager
{
public:
	IGBossZoneGateManager();
	~IGBossZoneGateManager();
	
	void OpenGate();	

	static TSharedPtr<IGBossZoneGateManager> GetInstance();

	FOpenGate_Dele FOpenGateDelegate;
private:
};
