// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGHintMonsterBase.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Engine/DamageEvents.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/AI/WIspAI/IGWispAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interactable/IGMountainCrystal.h"
#include "Indigo/Interactable/IGWaveCrystal.h"
#include "Indigo/Interactable/IGTreeCrystal.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SK_Monster.SK_Monster'"), [&](USkeletalMesh* MeshRef)
{
	GetMesh()->SetSkeletalMesh(MeshRef);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}, EAssertionLevel::Check);
	
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
	RootComponent = GetCapsuleComponent();

	AIControllerClass = AIGWispAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;
	
	bIsAttack = false;
	bIsDelay = false;
	bIsRetreating = false;
	RespawnTime = 0.0f;
	AttackDelay = 4.0f;
	ElapsedTime = 0.0f;
	AttackTime  = 0.0f;
	RetreatTime = 0.0f;
	StoppingDistance = 200.0f;
	AttackSpeed = 800.0f;
	
}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	
	
	AIGEnemyBase::SetHp(1);
	SpawnPos = GetActorLocation();
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttack)
	{
		AddActorLocalOffset(DashStartLocation * DeltaTime * AttackSpeed);
		AttackTime += DeltaTime;
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
			FCollisionShape::MakeSphere(50),
			CollisionParams
		);
		DrawDebugSphere(GWorld, GetActorLocation(), 50, 16, FColor::Green, false, 0.f);
		
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
				AttackTime = 0.0f;
				EndAttack();
			}
		}
		if((GetActorLocation() - AttackStartLocation).Size() >= StoppingDistance || AttackTime >= 0.5f)
		{
			bIsAttack = false;
			bIsRetreating = true;
			RetreatStartLocation = GetActorLocation();
			RetreatEndLocation = DashStartLocation;
			AttackTime = 0.0f;
			EndAttack();
		}
	}
	if (bIsRetreating)
	{
		FVector TargetPos = (AttackStartLocation - GetActorLocation()).GetSafeNormal();
		AddActorLocalOffset(TargetPos * DeltaTime * AttackSpeed);
		RetreatTime += DeltaTime;
		if ((GetActorLocation() - RetreatStartLocation).Size() >= StoppingDistance / 2 || RetreatTime >= 0.5f)
		{
			bIsRetreating = false;
			RetreatTime = 0.0f;			
		}
	}
}

void AIGHintMonsterBase::DropCrystal()
{
	const int8 CrystalDropPercent = FMath::RandRange(0,1);
	
	if(CrystalDropPercent == 1)
	{	
		if(CrystalType == ECrystal::Mountain)
		{
			AIGMountainCrystal* MountainCrystal = GetWorld()->SpawnActor<AIGMountainCrystal>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);					
		}
		else if(CrystalType == ECrystal::Tree)
		{
			AIGTreeCrystal* TreeCrystal = GetWorld()->SpawnActor<AIGTreeCrystal>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);					
		}
		else if(CrystalType == ECrystal::Wave)
		{
			AIGWaveCrystal* WaveCrystal = GetWorld()->SpawnActor<AIGWaveCrystal>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);					
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("결정파편 드랍 안됨!")));
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
		bIsDead = true;
		DropCrystal();
		SetActorLocation(SpawnPos);
	    FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
            {
        		this->SetActorEnableCollision(true);
				this->SetActorHiddenInGame(false);
				AIGEnemyBase::SetHp(1);
        		bIsDead = false;
                GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
            }), 3.0f, false);			
	}	

	return DamageAmount;
}

void AIGHintMonsterBase::PerformCloseAttack()
{
	if(bIsAttack)
	{
		return;
	}
	
	AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));
	if(Player == nullptr)
	{
		return;
	}
	
	FVector TargetVector =  (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	AttackStartLocation = GetActorLocation();
	bIsAttack = true;
	DashStartLocation = TargetVector;
	DashEndLocation = TargetVector * StoppingDistance;
}

void AIGHintMonsterBase::EndAttack()
{
	OnFinishWispAttack.Broadcast();
}