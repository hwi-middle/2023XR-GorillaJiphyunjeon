// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossGatePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

AIGBossGatePlace::AIGBossGatePlace()
{
	bIsOpen = false;
}

void AIGBossGatePlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGBossGatePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();

	if(bIsOpen == false)
	{
		return;
	}

	PlayerCharacter->GetShinmyophil()->ProvisoRemakeOpenGateAndCloseToGate();
	Destroy();
	
}

void AIGBossGatePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
