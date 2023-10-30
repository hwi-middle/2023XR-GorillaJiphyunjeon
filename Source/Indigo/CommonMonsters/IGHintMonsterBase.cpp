// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintMonsterBase.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Engine/DamageEvents.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Interactable/IGBlankHint.h"
#include "Indigo/Interactable/IGMainHint.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/AI/WIspAI/IGWispAIController.h"
#include "Indigo/PhasePlace/ProvisoPhase/IGProvisoWispPlace.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SK_Monster.SK_Monster'"), [&](USkeletalMesh* MeshRef)
{
	GetMesh()->SetSkeletalMesh(MeshRef);
	RootComponent = GetMesh();
}, EAssertionLevel::Check);

	AIControllerClass = AIGWispAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	bIsAttack = false;
	bIsFirstAttack = false;
	bIsDelay = false;
	bIsRetreating = false;
	RespawnTime = 0.0f;
	AttackDelay = 4.0f;
	ElapsedTime = 0.0f;
	AttackTime  = 0.0f;
	StoppingDistance = 200.0f;
	
}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	

	
	WispPlace = GetWorld()->SpawnActor<AIGProvisoWispPlace>(AIGProvisoWispPlace::StaticClass(), GetActorLocation(), GetActorRotation());
	WispPlace->SetActorScale3D(GetActorScale() * 5);
	
	AIGEnemyBase::SetHp(1);
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	if(bIsFirstAttack)
	{
		StoppingDistance = 100.0f;
	}
	else
	{
		StoppingDistance = 200.0f;
	}

	if(bIsDelay)
	{
		ElapsedTime += DeltaTime;
		if(ElapsedTime >= AttackDelay)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("딜레이 4초")));
			bIsDelay = false;
			ElapsedTime = 0.0f;
			EndAttack();
		}
			return;
	}
	
	
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (bIsAttack)
	{
		AddActorLocalOffset(DashStartLocation * DeltaTime * 400);

		FHitResult Result;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		DrawDebugSphere(GetWorld(), GetActorLocation(), GetActorScale().X, 16, FColor::Green, false, 0.f);

		bool bHit = GetWorld()->SweepSingleByChannel(
			Result,
			GetActorLocation(),
			GetActorLocation(),
			FQuat::Identity,
			ECC_CHECK_PAWN,
			FCollisionShape::MakeSphere(GetActorScale().X),
			CollisionParams
		);

		if (bHit)
		{
			AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor());
			if (Player != nullptr)
			{
				FDamageEvent DamageEvent;
				Player->TakeDamage(5.f, DamageEvent, GetInstigatorController(), this);
				bIsAttack = false;
				bIsRetreating = true;
				RetreatStartLocation = GetActorLocation();
				RetreatEndLocation = DashStartLocation;
				RetreatStartTime = CurrentTime;
				RetreatEndTime = RetreatStartTime + 0.5f;
			}
		}		
		else if ((GetActorLocation() - AttackStartLocation).Size() > StoppingDistance * 2)
		{
			bIsAttack = false;			
			bIsRetreating = true;
			RetreatStartLocation = GetActorLocation();
			RetreatEndLocation =  DashStartLocation; 
			RetreatStartTime = CurrentTime;
			RetreatEndTime = RetreatStartTime + 0.5f;
			
		}
	}
	else if (bIsRetreating)
	{
		FVector TargetPos = (AttackStartLocation - GetActorLocation()).GetSafeNormal2D();
		//TargetPos.Normalize();
		AddActorLocalOffset(TargetPos * DeltaTime * 400.0f);

		if ((GetActorLocation() - RetreatStartLocation).Size() > StoppingDistance * 2)
		{
			bIsRetreating = false;
			bIsDelay = true;

		}
	}
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
			MainHint->InitHintType(HintType);		
		}
		else
		{
			AIGBlankHint* BlankHint = GetWorld()->SpawnActor<AIGBlankHint>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
			BlankHint->InitHintType(EHintType::Blank);
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
	    FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
            {
        		this->SetActorEnableCollision(true);
				this->SetActorHiddenInGame(false);
				AIGEnemyBase::SetHp(1);
                GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
            }), 3.0f, false);
	
		DropHint();
	}	

	return DamageAmount;
}

void AIGHintMonsterBase::PerformCloseAttack()
{
	if(bIsDelay)
	{
		return;
	}
	
	AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));
	if(Player == nullptr)
	{
		return;
	}
	if(AIGWispAIController* Ai = Cast<AIGWispAIController>(AIControllerClass))
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("추격")));
		Ai->MoveToLocation(Player->GetActorLocation());
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("공격 호출")));
	FVector TargetVector =  (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	//TargetVector.Normalize();

	AttackStartLocation = GetActorLocation();
	bIsAttack = true;
	DashStartLocation = TargetVector;
	DashEndLocation = TargetVector * StoppingDistance;
	DashStartTime = FPlatformTime::Seconds();
	DashEndTime = DashStartTime + 0.5f;
	bIsFirstAttack = true;
}

void AIGHintMonsterBase::EndAttack()
{
	OnFinishWispAttack.Broadcast();
}