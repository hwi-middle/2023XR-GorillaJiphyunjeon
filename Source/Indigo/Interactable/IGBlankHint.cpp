// Copyright GorillaJiphyunjeon. All Rights Reserved.
#include "IGBlankHint.h"
#include "IGHintParent.h"

// Sets default values
AIGBlankHint::AIGBlankHint()
	:AIGHintParent(TEXT("/Script/Engine.DataTable'/Game/_GorillaJiphyunjeon/DataTable/ScriptDataTable/BlankHintScript.BlankHintScript'"))
{
	
}

// Called when the game starts or when spawned
void AIGBlankHint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGBlankHint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIGBlankHint::Interact()
{
	AIGHintParent::Interact();
}