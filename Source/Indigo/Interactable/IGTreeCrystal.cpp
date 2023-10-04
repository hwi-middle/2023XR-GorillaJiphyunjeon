// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTreeCrystal.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Indigo/Management/IGCrystalManager.h"



// Sets default values
AIGTreeCrystal::AIGTreeCrystal()
:AIGCrystalBase(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/ProvisoStoryScript.ProvisoStoryScript'"), TEXT("소나무"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGTreeCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGTreeCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGTreeCrystal::Interact()
{
	AIGCrystalBase::Interact();
}

void AIGTreeCrystal::TakeCrystal()
{
	AIGCrystalBase::TakeCrystal();
	
}