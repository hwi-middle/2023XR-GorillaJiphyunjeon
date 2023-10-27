// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProvisoOldTreePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/Inventory/IGShinmyophil.h"


AIGProvisoOldTreePlace::AIGProvisoOldTreePlace()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIGProvisoOldTreePlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGProvisoOldTreePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter == nullptr)
	{
		return;
	}

	if(PlayerCharacter->GetInventory()->GetCrystalArray().Num() < 9 && bIsInCollision == false)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoRemakeCantFindCrystalAndCloseToOldTree();
	}
}

void AIGProvisoOldTreePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
