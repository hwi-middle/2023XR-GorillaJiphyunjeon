// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveSectorMonster.h"

AIGWaveSectorMonster::AIGWaveSectorMonster()
{
}

void AIGWaveSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetCrystalType(ECrystal::Wave);
}

void AIGWaveSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
