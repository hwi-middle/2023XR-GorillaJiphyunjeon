// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintMonsterBase.h"

#include "AsyncTreeDifferences.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Interactable/IGBlankHint.h"
#include "Indigo/Interactable/IGMainHint.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoWispPlace.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SK_Monster.SK_Monster'"), [&](USkeletalMesh* MeshRef)
{
	GetMesh()->SetSkeletalMesh(MeshRef);
	RootComponent = GetMesh();
}, EAssertionLevel::Check);
	
RespawnTime = 0.0f;
}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	

	WispPlace = nullptr;
	WispPlace = GetWorld()->SpawnActor<AIGProvisoWispPlace>(AIGProvisoWispPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	WispPlace->SetActorScale3D(GetActorScale() * 5);
	HintType = EHintType::PineTree;
	
	// AIGEnemyBase::SetHp(9);
	AIGEnemyBase::SetHp(1);
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Hp <= 0)
	{
		RespawnTime += DeltaTime;
		if(RespawnTime >= 3.0f)
		{
			this->SetActorEnableCollision(true);
			this->SetActorHiddenInGame(false);
			AIGEnemyBase::SetHp(1);
			RespawnTime = 0.0f;
		}
	}
}

void AIGHintMonsterBase::DropHint()
{
	// const int8 HintDropPercent = FMath::RandRange(0,1);

	
	const int8 HintDropPercent = 1;
	
	if(HintDropPercent == 1)
	{		
		const int8 MainHintDropPercent = FMath::RandRange(0,1);
		
		if(MainHintDropPercent == 1)
		{
			AIGMainHint* MainHint = GetWorld()->SpawnActor<AIGMainHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			MainHint->InitHintType(HintType);		
		}
		else
		{
			AIGBlankHint* BlancHint = GetWorld()->SpawnActor<AIGBlankHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			BlancHint->InitHintType(EHintType::Blanc);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("힌트 드랍 안됨!")));
	}

	
	if(WispPlace != nullptr)
	{
		WispPlace->Destroy();
	}
	
	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
	
}

float AIGHintMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	SetHp(GetHp() - DamageAmount);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("[도깨비불 체력] %f"), GetHp()));
	if(GetHp() <= 0)
	{
		DropHint();
	}	

	return DamageAmount;
}



