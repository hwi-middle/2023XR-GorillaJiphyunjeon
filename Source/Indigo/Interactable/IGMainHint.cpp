// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainHint.h"
#include "IGHintParent.h"

// Sets default values
AIGMainHint::AIGMainHint()
	:AIGHintParent(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/MainHintScript.MainHintScript'"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIGMainHint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGMainHint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGMainHint::Interact()
{	
	AIGHintParent::Interact();
}