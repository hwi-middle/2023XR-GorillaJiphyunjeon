// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGCrystalBase.h"

#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Management/IGCrystalManager.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoCloseToCrystalPlace.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Util/IGDataTableParser.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIGCrystalBase::AIGCrystalBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AIGCrystalBase::AIGCrystalBase(FString InPath, FName InName)
{
	bIsTaken = false;


	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/Monster_iteam/SM_magatama.SM_magatama'"), [&](UStaticMesh* MeshRef)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		Mesh->SetStaticMesh(MeshRef);
		// Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		// Mesh->SetCollisionProfileName(TEXT("Evidence"));
		RootComponent = Mesh;
		Mesh->SetSimulatePhysics(true);
		Mesh->BodyInstance.bLockXRotation = true;
		Mesh->BodyInstance.bLockYRotation = true;
		Mesh->BodyInstance.bLockZRotation = true;
	}, EAssertionLevel::Check);

	FIGDataTableParser::LoadAndInitializeDataTable(*InPath, [&](const UDataTable* ScriptDataTable)
	{
		CrystalScript = ScriptDataTable->FindRow<FIGScriptDataTable>(InName,TEXT(""));
	});
}

// Called when the game starts or when spawned
void AIGCrystalBase::BeginPlay()
{
	Super::BeginPlay();

	CloseToCrystalPlace = GetWorld()->SpawnActor<AIGProvisoCloseToCrystalPlace>(AIGProvisoCloseToCrystalPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	CloseToCrystalPlace->SetActorScale3D(GetActorScale() * 5);
	
}

// Called every frame
void AIGCrystalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 150.f;

	TArray<AActor*> IgnoredWisps;
	TArray<AActor*> IgnoredCrystals;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIGHintMonsterBase::StaticClass(), IgnoredWisps);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), IgnoredCrystals);

	for (AActor* Wisps : IgnoredWisps)
	{
		CollisionParams.AddIgnoredActor(Wisps);
	}
	for (AActor* Crystals : IgnoredCrystals)
	{
		CollisionParams.AddIgnoredActor(Crystals);
	}

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);

	if (!bHit)
	{
		return;
	}

	if (AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor()))
	{
		Take();
		
		if(CloseToCrystalPlace != nullptr)
		{
			CloseToCrystalPlace->Destroy();
		}

		Player->AddCrystal(this);
		
		Destroy();
	}
}

void AIGCrystalBase::Interact()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%s]"), *CrystalScript->Script));
	// Take();
	//
	// if(CloseToCrystalPlace != nullptr)
	// {
	// 	CloseToCrystalPlace->Destroy();
	// }
	//
	// Destroy();
}

void AIGCrystalBase::Take()
{
	if (bIsTaken)
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("[%s]의 결정 습득"), *CrystalScript->Name));

	bIsTaken = true;

	Destroy();
}
