// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGVillageGate.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGVillageGate::AIGVillageGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/BossDoor/Wall_small01.Wall_small01'"), [&](UStaticMesh* MeshRef)
    	{
    	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    	Mesh->SetStaticMesh(MeshRef);
    	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
    	Mesh->SetCollisionProfileName(TEXT("Evidence"));
    	RootComponent = Mesh;
    	}, EAssertionLevel::Check);
    
    	OffSet = FVector(0.0f, 0.0f, 100.0f);
    	bIsOpen = false;
    	ElapsedTime = 0.0f;
		RotationTime = 2.0f;

	StartRotation = GetActorRotation();
	TargetRotation = StartRotation + FRotator(0.0f, 90.0f, 0.0f);


}

// Called when the game starts or when spawned
void AIGVillageGate::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGVillageGate::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIGVillageGate::OpenGate()
{
	if(bIsOpen == true)
	{
		return;
	}

	
	bIsOpen = true;
}

void AIGVillageGate::Interact()
{
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(this, 0);
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerCharacter);
	
	if(bIsOpen == false || IGPlayerCharacter == nullptr)
	{
		return;
	}

	IGPlayerCharacter->GetShinmyophil()->TutorialInteractToGate();

	
}

// Called every frame
void AIGVillageGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
		
	if(bIsOpen == false)
	{
		return;
	}
		
	if(ElapsedTime < RotationTime )
	{		
		ElapsedTime += DeltaTime;
		float Alpha = ElapsedTime / RotationTime;
		FRotator InterpolatedRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
		SetActorRotation(InterpolatedRotation);
	}
	else
	{
		SetActorRotation(TargetRotation);
	}

}

