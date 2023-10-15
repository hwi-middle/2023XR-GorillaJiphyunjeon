// Copyright GorillaJiphyunjeon. All Rights Reserved.
#include "IGBlankHint.h"
#include "IGHintBase.h"

// Sets default values
AIGBlankHint::AIGBlankHint()
{
	InitHintType(EHintType::Blanc);
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
	AIGHintBase::Interact();
}