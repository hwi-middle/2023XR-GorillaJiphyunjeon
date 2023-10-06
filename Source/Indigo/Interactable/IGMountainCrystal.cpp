// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainCrystal.h"




// Sets default values
AIGMountainCrystal::AIGMountainCrystal()
	:AIGCrystalBase(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/ProvisoStoryScript.ProvisoStoryScript'"), TEXT("바위산"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CrystalType = ECrystal::Mountain;
	

}

// Called when the game starts or when spawned
void AIGMountainCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AIGMountainCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGMountainCrystal::Interact()
{
	AIGCrystalBase::Interact();
}



void AIGMountainCrystal::Take()
{
	AIGCrystalBase::Take();
}