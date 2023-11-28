// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGGate.h"

#include "Components/BoxComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGBossGatePlace.h"
#include "Indigo/Management/IGBossZoneGateManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGGate::AIGGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/Gatehouse/SM_gatehouse_door.SM_gatehouse_door'"), [&](UStaticMesh* MeshRef)
	{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionProfileName(TEXT("Evidence"));
	RootComponent = Mesh;
	}, EAssertionLevel::Check);

	IGBossZoneGateManager::GetInstance()->FOpenGateDelegate.BindUFunction(this, TEXT("OpenGate"));
	OffSet = FVector(0.0f, 0.0f, 100.0f);
	bIsOpen = false;
	ElapsedTime = 0.0f;
	RotationTime = 2.0f;

	StartRotation = GetActorRotation();
	TargetRotation = StartRotation + FRotator(0.0f, 90.0f, 0.0f);

	BoxCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AIGGate::BeginPlay()
{
	Super::BeginPlay();

	BossGatePlace = GetWorld()->SpawnActor<AIGBossGatePlace>(AIGBossGatePlace::StaticClass(), GetActorLocation(), GetActorRotation());
	BossGatePlace->SetActorScale3D(GetActorScale()*50);

	
}

void AIGGate::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	IGBossZoneGateManager::GetInstance()->FOpenGateDelegate.Unbind();
}

void AIGGate::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	UGameplayStatics::OpenLevel(this, TEXT("BOSS"));
}

// Called every frame
void AIGGate::Tick(float DeltaTime)
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
		SetActorRelativeRotation(InterpolatedRotation);
	}
	else
	{
		SetActorRelativeRotation(TargetRotation);
	}
	
}

void AIGGate::OpenGate()
{
	if(bIsOpen)
	{
		return;
	}
	
	bIsOpen = true;
	BossGatePlace->SetIsOpen(true);
}

void AIGGate::Interact()
{
	APawn* PlayerController = UGameplayStatics::GetPlayerPawn(GWorld, 0);
	const AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerController);

	if(IGPlayerCharacter == nullptr)
	{
		return;
	}
	
	if(!bIsOpen)
	{
		IGPlayerCharacter->GetShinmyophil()->ProvisoRemakeBeforeOpenGateAndInteractToGate();
		return;
	}
	IGPlayerCharacter->GetShinmyophil()->ProvisoRemakeOpenGateAndInteractToGate();

}

