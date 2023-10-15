// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProvisoWispPlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

AIGProvisoWispPlace::AIGProvisoWispPlace()
{
}

void AIGProvisoWispPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGProvisoWispPlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoFirstMeetingWist();
		Destroy();
	}
}

void AIGProvisoWispPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
