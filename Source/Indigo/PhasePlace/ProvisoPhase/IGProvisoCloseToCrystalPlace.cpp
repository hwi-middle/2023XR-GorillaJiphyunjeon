// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProvisoCloseToCrystalPlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"


AIGProvisoCloseToCrystalPlace::AIGProvisoCloseToCrystalPlace()
{
}

void AIGProvisoCloseToCrystalPlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGProvisoCloseToCrystalPlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoCloseToProviso();
		Destroy();
	}
}

void AIGProvisoCloseToCrystalPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
