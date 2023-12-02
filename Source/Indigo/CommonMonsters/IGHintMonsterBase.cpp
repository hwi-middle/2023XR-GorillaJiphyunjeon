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
#include "Indigo/Animation/IGWispAnimInstance.h"
#include "Indigo/Interactable/IGHealKit.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Indigo/DataAsset/IGWispDataAsset.h"
#include "Sound/SoundCue.h"
#include "NiagaraComponent.h"

// Sets default values
AIGHintMonsterBase::AIGHintMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_A.SM_Monster_A'"), [&](USkeletalMesh* MeshRef)
{
	GetMesh()->SetSkeletalMesh(MeshRef);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}, EAssertionLevel::Check);
	
	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_A/ABP_Wisp.ABP_Wisp_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);
	
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	RootComponent = GetCapsuleComponent();

	WispDataAsset = FIGConstructorHelper::FindAndGetObject<UIGWispDataAsset>(TEXT("/Script/Indigo.IGWispDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_WispData.DA_WispData'"));
	
	AIControllerClass = AIGWispAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
		

	GetCharacterMovement()->MaxWalkSpeed = WispDataAsset->Speed;

	bIsHit = false;
	bIsAttack = false;
	bIsDelay = false;
	bIsRetreating = false;
	RespawnTime = 10.0f;
	AttackDelay = 4.0f;
	ElapsedTime = 0.0f;
	AttackTime  = 0.0f;
	RetreatTime = 0.0f;
	StoppingDistance = 500.0f;
	ExplosionDistance = 250.0f;
	AttackSpeed = 800.0f;
	
}

// Called when the game starts or when spawned
void AIGHintMonsterBase::BeginPlay()
{
	Super::BeginPlay();	
	
	Wisp_MaxHp = WispDataAsset->MaxHp;
	
	BombDamage = WispDataAsset->BombDamage;
	DashDamage = WispDataAsset->DashDamage;

	CrystalPercent = WispDataAsset->CrystalPercent;
	HealKitPercent = WispDataAsset->HealkitPercent;


	AIGEnemyBase::SetHp(Wisp_MaxHp);
	SpawnPos = GetActorLocation();

	AnimInstance = CastChecked<UIGWispAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnFinishHit.AddUObject(this, &AIGHintMonsterBase::IsHitFinish);
	AnimInstance->OnWispExplosion.AddUObject(this, &AIGHintMonsterBase::Explosion);
	AnimInstance->OnFinishBomb.AddUObject(this, &AIGHintMonsterBase::EndAttack);
	SetActorRotation(FRotator(0, 0, 0));
}

// Called every frame
void AIGHintMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsDead || bIsHit)
	{
		return;
	}
	
	if (bIsAttack)
	{
		AddActorLocalOffset(DashStartLocation * DeltaTime * AttackSpeed);
		AttackTime += DeltaTime;
		FHitResult Result;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		//DrawDebugSphere(GetWorld(), GetActorLocation(), GetActorScale().X, 16, FColor::Green, false, 0.f);

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
				Player->TakeDamage(DashDamage, DamageEvent, GetInstigatorController(), this);
				bIsAttack = false;
				bIsRetreating = true;
				RetreatStartLocation = GetActorLocation();
				RetreatEndLocation = DashStartLocation;
				AttackTime = 0.0f;
				//강제 되돌림
				AnimInstance->AnimNotify_FinishDash();
				EndAttack();
			}
		}
		if((GetActorLocation() - AttackStartLocation).Size() >= 500 || AttackTime >= 1.0f)
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
		AddActorLocalOffset(TargetPos * DeltaTime * AttackSpeed/2);
		RetreatTime += DeltaTime;
		if ((GetActorLocation() - RetreatStartLocation).Size() > ExplosionDistance/2 || RetreatTime >= 0.4f)
		{
			bIsRetreating = false;
			RetreatTime = 0.0f;			
		}
	}
}

void AIGHintMonsterBase::DropCrystal()
{
	const int8 DropPercent = FMath::RandRange(1,100);
	
	if(DropPercent <= CrystalPercent)
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
	else if (HealKitPercent + CrystalPercent <= 100)
	{
		if (DropPercent <= HealKitPercent + CrystalPercent)
		{
			AIGHealKit* HealKit = GetWorld()->SpawnActor<AIGHealKit>(GetActorTransform().GetLocation(), FRotator::ZeroRotator);
		}
	}

	

	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);	
}

float AIGHintMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(bIsDead)
	{
		return 0.0f;
	}
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->WispHitSoundCue);
	
	AnimInstance->OnHit();
	bIsHit = true;
	
	SetHp(GetHp() - DamageAmount);
	if(GetHp() <= 0)
	{
		UGameplayStatics::PlaySound2D(this, SoundDataAsset->WispDeadSoundCue);
		bIsDead = true;

		
		//피격 애니메이션 재생 안하고 체력 떨어지면 바로 사망 
		DropCrystal();			
		GetWorldTimerManager().SetTimerForNextTick(this, &AIGHintMonsterBase::PendRespawn);

	}	

	return DamageAmount;
}

void AIGHintMonsterBase::PendRespawn()
{
	static float ElapsedRespawnTime = 0.f;
	constexpr float Duration = 10.f;
	const float DeltaTime = GWorld->GetDeltaSeconds();
	ElapsedRespawnTime += DeltaTime;

	if (ElapsedRespawnTime >= Duration)
	{
		SetActorLocation(SpawnPos);
		this->SetActorEnableCollision(true);
		this->SetActorHiddenInGame(false);
		AIGEnemyBase::SetHp(Wisp_MaxHp);
		bIsDead = false;
		AttackSpeed = 800;
		ElapsedTime = 0.f;
		ElapsedRespawnTime = 0.0f;
		return;
	}
	GetWorldTimerManager().SetTimerForNextTick(this, &AIGHintMonsterBase::PendRespawn);
}

void AIGHintMonsterBase::PerformCloseAttack()
{
	if(bIsAttack || bIsDead)
	{
		return;
	}
	
	AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));
	if(Player == nullptr)
	{
		return;
	}

	AnimInstance->OnDash();
	
	FVector TargetVector =  (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	AttackStartLocation = GetActorLocation();
	bIsAttack = true;
	DashStartLocation = TargetVector;
	DashEndLocation = DashStartLocation * StoppingDistance;
}

void AIGHintMonsterBase::PerformBombAttack()
{
	AnimInstance->OnExplosion();	
}

void AIGHintMonsterBase::Explosion()
{
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->WispBombSoundCue);
	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->SweepSingleByChannel(
	Result,
	GetActorLocation(),
	GetActorLocation(),
	FQuat::Identity,
	ECC_CHECK_PAWN,
	FCollisionShape::MakeSphere(250),
	CollisionParams
);
	DrawDebugSphere(GWorld, GetActorLocation(), 250, 16, FColor::Green, false, 0.f);
		
	if (bHit)
	{
		AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor());
		if (Player != nullptr)
		{
			FDamageEvent DamageEvent;
			Player->TakeDamage(BombDamage, DamageEvent, GetInstigatorController(), this);
		}
	}
}

void AIGHintMonsterBase::EndAttack()
{
	OnFinishWispAttack.Broadcast();
}
