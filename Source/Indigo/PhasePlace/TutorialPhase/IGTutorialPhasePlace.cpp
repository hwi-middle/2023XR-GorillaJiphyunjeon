// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutorialPhasePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"

// Sets default values
AIGTutorialPhasePlace::AIGTutorialPhasePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGTutorialPhasePlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGTutorialPhasePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetShinmyophil()->OnTutorialPhase();
		Destroy();
	}
}

// Called every frame
void AIGTutorialPhasePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

