// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGTutorialJangseung.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "IGTutorialJangseungPlace.h"
#include "Indigo/Object/IGVillageGate.h"
#include "Kismet/GameplayStatics.h"

AIGTutorialEnemyJangseung::AIGTutorialEnemyJangseung()
{
		FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/StaticMesh/Totem/SM_Korean_totem01.SM_Korean_totem01'"), [&](UStaticMesh* MeshRef)
	{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshRef);
	RootComponent = Mesh;
	}, EAssertionLevel::Check);

	
	
	DamageCount = 0;
}

void AIGTutorialEnemyJangseung::BeginPlay()
{
	Super::BeginPlay();
	AIGTutorialJangseungPlace* LocalActor = GetWorld()->SpawnActor<AIGTutorialJangseungPlace>(AIGTutorialJangseungPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	LocalActor->Setsize(GetActorScale() * 2);

	
}

void AIGTutorialEnemyJangseung::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AIGTutorialEnemyJangseung::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageCount++;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("[%d]"), DamageCount));			
	PlayerCharacter = UGameplayStatics::GetPlayerPawn(GWorld, 0);
	if (PlayerCharacter != nullptr)
	{
		AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerCharacter);

		if(DamageCount == 3)
		{
			IGPlayerCharacter->GetShinmyophil()->TutorialAttackToJangseung3Times();
		}
		else if(DamageCount >= 3 && EnumHasAnyFlags(IGPlayerCharacter->GetCurrentState(), EPlayerState::Enforced) == true)
		{
			IGPlayerCharacter->GetShinmyophil()->TutorialEnforceAttackToJangseung();
			OpenGate();				
			Destroy();
		}
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

void AIGTutorialEnemyJangseung::OpenGate()
{
	PlayerCharacter = UGameplayStatics::GetPlayerPawn(GWorld, 0);
	AIGPlayerCharacter* IGPlayerCharacter = Cast<AIGPlayerCharacter>(PlayerCharacter);

	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIGVillageGate::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
		{
			AIGVillageGate* VillagageGate = Cast<AIGVillageGate>(Actor);
			if(VillagageGate != nullptr)
			{
				IGPlayerCharacter->GetShinmyophil()->TutorialOpenGate();
				VillagageGate->OpenGate();
			}
	}
	
}

