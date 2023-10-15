// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBattlePhasePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"


// Sets default values
AIGBattlePhasePlace::AIGBattlePhasePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGBattlePhasePlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGBattlePhasePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetShinmyophil()->OnBattlePhase();
		Destroy();
	}
}

// Called every frame
void AIGBattlePhasePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

