// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPineTreeSectorMonster.h"

// Sets default values
AIGPineTreeSectorMonster::AIGPineTreeSectorMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AIGPineTreeSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetCrystalType(ECrystal::Tree);
}

// Called every frame
void AIGPineTreeSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

