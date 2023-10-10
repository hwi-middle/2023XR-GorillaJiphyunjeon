// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBoss.h"

#include "IGPlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/AI/IGBossAIController.h"
#include "Indigo/Animation/IGBossAnimInstance.h"
#include "Indigo/Battle/IGMountainSpike.h"
#include "Indigo/Constant/IGBossSockets.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/DataAsset/IGBossGimmickDataAsset.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"

AIGBoss::AIGBoss()
{
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Mesh/SK_Boss.SK_Boss'"), [&](USkeletalMesh* MeshRef)
	{
		GetMesh()->SetSkeletalMesh(MeshRef);
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	}, EAssertionLevel::Check);

	const TSubclassOf<UIGBossAnimInstance> BossAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGBossAnimInstance>(
		TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Animation/ABP_Boss.ABP_Boss_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(BossAnimInstanceClass);

	AIControllerClass = AIGBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	GimmickDataAsset = FIGConstructorHelper::FindAndGetObject<UIGBossGimmickDataAsset>(TEXT("/Script/Indigo.IGBossGimmickDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_BossGimmickData.DA_BossGimmickData'"));
}

void AIGBoss::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = CastChecked<UIGBossAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetSpeed(0.f);
	AnimInstance->OnGenerateBossCloseAttack.AddUObject(this, &AIGBoss::GenerateCloseAttack);
	AnimInstance->OnFinishAttack.AddUObject(this, &AIGBoss::EndCloseAttack);
	StoppingDistance = 400.f;
	CloseAttack_SpikeNum = GimmickDataAsset->CloseAttack_SpikeNum;
	CloseAttack_HandRadius = GimmickDataAsset->CloseAttack_HandRadius;
	CloseAttack_Damage = GimmickDataAsset->CloseAttack_Damage;
	CloseAttack_SpikeTimeGap = GimmickDataAsset->CloseAttack_SpikeTimeGap;
	CloseAttack_SpikeDistanceGap = GimmickDataAsset->CloseAttack_SpikeDistanceGap;
	CloseAttack_SpikeDuration = GimmickDataAsset->CloseAttack_SpikeDuration;
	CloseAttack_SpikeDestroyDelay = GimmickDataAsset->CloseAttack_SpikeDestroyDelay;
}

void AIGBoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AnimInstance->SetSpeed(GetVelocity().Size2D());

	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_LEFT_HAND), 100.f, 16, FColor::Red, false, 0.f);
	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_RIGHT_HAND), 100.f, 16, FColor::Red, false, 0.f);
}

void AIGBoss::PerformCloseAttack()
{
	AnimInstance->StartCloseAttack();
}

void AIGBoss::GenerateCloseAttack()
{
	// 주먹에 의한 피해
	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	DrawDebugSphere(GetWorld(), GetActorLocation(), CloseAttack_HandRadius, 16, FColor::Green, false, 0.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetMesh()->GetSocketLocation(BOSS_RIGHT_HAND),
		GetMesh()->GetSocketLocation(BOSS_RIGHT_HAND),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(CloseAttack_HandRadius),
		CollisionParams
	);

	if (bHit)
	{
		AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor());
		if (Player)
		{
			FDamageEvent DamageEvent;
			Player->TakeDamage(10.f, DamageEvent, GetInstigatorController(), this);
		}
	}

	// 산 생성
	FVector TargetVector = UGameplayStatics::GetPlayerPawn(GWorld, 0)->GetActorLocation() - GetActorLocation();
	TargetVector.Normalize();

	for (uint32 i = 0; i < CloseAttack_SpikeNum; i++)
	{
		constexpr float Height = 300.f;
		FVector GenerationLocation = GetActorLocation() + TargetVector * CloseAttack_SpikeDistanceGap * (i + 1);
		GenerationLocation.Z = -Height;
		AIGMountainSpike* SpawnedSpike = GWorld->SpawnActor<AIGMountainSpike>(GenerationLocation, FRotator::ZeroRotator);
		SpawnedSpike->Init(CloseAttack_Damage, 300.f, CloseAttack_SpikeTimeGap * i, CloseAttack_SpikeDuration, CloseAttack_SpikeDestroyDelay);
	}
}

void AIGBoss::EndCloseAttack()
{
	OnFinishBossCloseAttack.Broadcast();
}
