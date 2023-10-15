// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrack.h"
#include "Components/BoxComponent.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGCrack::AIGCrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	BoxCollider->SetCollisionProfileName(TEXT("Evidence"));
}

void AIGCrack::Interact()
{
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GWorld, 0);
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerCharacter);
	if(PlayerCharacter == nullptr || IGPlayerCharacter == nullptr)
	{
		return;
	}

	IGPlayerCharacter->GetShinmyophil()->TutorialPlayerCrackInteract();	
}

// Called when the game starts or when spawned
void AIGCrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIGCrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

