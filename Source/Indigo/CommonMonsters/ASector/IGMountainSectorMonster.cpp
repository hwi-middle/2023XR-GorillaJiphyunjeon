// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainSectorMonster.h"

AIGMountainSectorMonster::AIGMountainSectorMonster()
{
	
}

void AIGMountainSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetHintType(EHintType::Mountain);	
	
}

void AIGMountainSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
