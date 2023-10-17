// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveSectorMonster.h"

AIGWaveSectorMonster::AIGWaveSectorMonster()
{
}

void AIGWaveSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetHintType(EHintType::Wave);
}

void AIGWaveSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
