// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutorialRollPlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

AIGTutorialRollPlace::AIGTutorialRollPlace()
{
}

void AIGTutorialRollPlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGTutorialRollPlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetShinmyophil()->TutorialRollCrack();
		Destroy();
	}
}

void AIGTutorialRollPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
