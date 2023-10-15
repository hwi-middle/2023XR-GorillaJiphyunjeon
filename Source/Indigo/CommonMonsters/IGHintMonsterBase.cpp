// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintMonsterBase.h"

#include "AsyncTreeDifferences.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "Indigo/Interactable/IGBlankHint.h"
#include "Indigo/Interactable/IGMainHint.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoWispPlace.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AIGHintMonsterBase::AIGHintMonsterBase(const FString InSectorName)
	:SectorName(InSectorName)
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SK_Monster.SK_Monster'"), [&](USkeletalMesh* MeshRef)
{
	GetMesh()->SetSkeletalMesh(MeshRef);
	RootComponent = GetMesh();
}, EAssertionLevel::Check);

	if(InSectorName == TEXT("소나무"))
	{
		HintType = EHintType::PineTree;
	}
	else if(InSectorName == TEXT("산"))
	{
		HintType = EHintType::Mountain;
		
	}
	else if(InSectorName == TEXT("물결"))
	{
		HintType = EHintType::Wave;		
	}
	else
	{
		HintType = EHintType::Blanc;		
	}

}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	

	AIGProvisoWispPlace* LocalActor = GetWorld()->SpawnActor<AIGProvisoWispPlace>(AIGProvisoWispPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	LocalActor->SetActorScale3D(GetActorScale() * 5);
	
	AIGEnemyBase::SetHp(9);
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AIGHintMonsterBase::DropHint()
{
	const int8 HintDropPercent = FMath::RandRange(0,1);
	
	if(HintDropPercent == 1)
	{		
		const int8 MainHintDropPercent = FMath::RandRange(0,1);
		
		if(MainHintDropPercent == 1)
		{
			AIGMainHint* MainHint = GetWorld()->SpawnActor<AIGMainHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("메인 힌트 드랍!")));
			MainHint->InitHintType(HintType);
		}
		else
		{
			GetWorld()->SpawnActor<AIGBlankHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("꽝 힌트 드랍!")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("힌트 드랍 안됨!")));
	}
	
	Destroy();
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



