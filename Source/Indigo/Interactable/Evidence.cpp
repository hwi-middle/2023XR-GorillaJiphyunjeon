// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Evidence.h"

// Sets default values
AEvidence::AEvidence()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AEvidence::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEvidence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEvidence::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("단서 상호작용"));
}

