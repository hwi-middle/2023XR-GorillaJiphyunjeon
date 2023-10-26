// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProvisoPhasePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

// Sets default values
AIGProvisoPhasePlace::AIGProvisoPhasePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGProvisoPhasePlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGProvisoPhasePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	
	PlayerCharacter->GetShinmyophil()->OnProvisoPhase();
	Destroy();
	
}

// Called every frame
void AIGProvisoPhasePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

