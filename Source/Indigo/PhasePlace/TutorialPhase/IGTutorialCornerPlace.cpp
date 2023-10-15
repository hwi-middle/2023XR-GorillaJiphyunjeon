// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutorialCornerPlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

AIGTutorialCornerPlace::AIGTutorialCornerPlace()
{
}

AIGTutorialCornerPlace::~AIGTutorialCornerPlace()
{
}

void AIGTutorialCornerPlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGTutorialCornerPlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();

	PlayerCharacter->GetShinmyophil()->TutorialPlayerOvertheCorner();
	Destroy();
	
	
}

void AIGTutorialCornerPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
