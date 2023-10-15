// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutorialJangseungPlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

AIGTutorialJangseungPlace::AIGTutorialJangseungPlace()
{
}

void AIGTutorialJangseungPlace::Setsize(const FVector InScale)
{
	SetActorScale3D(InScale);
}

void AIGTutorialJangseungPlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGTutorialJangseungPlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();

	if(PlayerCharacter == nullptr)
	{
		return;
	}
	PlayerCharacter->GetShinmyophil()->TutorialCloseToJangseung();
	Destroy();
}

void AIGTutorialJangseungPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
