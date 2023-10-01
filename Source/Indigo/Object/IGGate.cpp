// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGGate.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Management/IGBossZoneGateManager.h"

// Sets default values
AIGGate::AIGGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/SampleSphere/SM_SampleSphere.SM_SampleSphere'"), [&](UStaticMesh* MeshRef)
	{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RootComponent = Mesh;
	}, EAssertionLevel::Check);

	IGBossZoneGateManager::GetInstance()->FOpenGateDelegate.BindUFunction(this, TEXT("OpenGate"));
	OffSet = FVector(0.0f, 0.0f, 100.0f);
	bIsOpen = false;
	PerSecond = 0.0f;
}

// Called when the game starts or when spawned
void AIGGate::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIGGate::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	IGBossZoneGateManager::GetInstance()->FOpenGateDelegate.Unbind();
}

// Called every frame
void AIGGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		
	if(bIsOpen &&  PerSecond < 2 )
	{
		PerSecond += DeltaTime;		
		AddActorLocalOffset(OffSet*DeltaTime);		
	}
	
}

void AIGGate::OpenGate()
{
	if(bIsOpen == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("문은 이미 열렸어")));
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("문이 열렸으니 보스를 잡자")));
	bIsOpen = true;
}

