// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveCrystal.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Management/IGCrystalManager.h"


// Sets default values
AIGWaveCrystal::AIGWaveCrystal()
:AIGCrystalParent(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/ProvisoStoryScript.ProvisoStoryScript'"), TEXT("파도"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGWaveCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGWaveCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGWaveCrystal::Interact()
{
	AIGCrystalParent::Interact();
}

void AIGWaveCrystal::TakeCrystal()
{
	AIGCrystalParent::TakeCrystal();
}