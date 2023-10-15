// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGASectorMonster.h"

// Sets default values
AIGASectorMonster::AIGASectorMonster()
	:AIGHintMonsterBase("소나무")
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AIGASectorMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGASectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

