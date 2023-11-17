// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBoss.h"

#include "IGPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/AI/IGBossAIController.h"
#include "Indigo/Animation/IGBossAnimInstance.h"
#include "Indigo/Battle/IGBossFlooringProjectile.h"
#include "Indigo/Battle/IGFollowProjectile.h"
#include "Indigo/Battle/IGMountainSpike.h"
#include "Indigo/Battle/IGProjectileBase.h"
#include "Indigo/Battle/IGStraightProjectile.h"
#include "Indigo/Battle/IGTreeTorus.h"
#include "Indigo/Constant/IGBossSockets.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/DataAsset/IGBossDataAsset.h"
#include "Indigo/DataAsset/IGBossGimmickDataAsset.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/UI/IGIngameHUDWidget.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"

AIGBoss::AIGBoss()
{
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Mesh/SM_Boss_Rigging.SM_Boss_Rigging'"), [&](USkeletalMesh* MeshRef)
	{
		GetMesh()->SetSkeletalMesh(MeshRef);
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	}, EAssertionLevel::Check);

	const TSubclassOf<UIGBossAnimInstance> BossAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGBossAnimInstance>(
		TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Animation/ABP_Boss.ABP_Boss_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(BossAnimInstanceClass);

	InteractCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollider"));
	InteractCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	InteractCollider->SetCollisionProfileName(TEXT("Evidence"));
	InteractCollider->SetupAttachment(GetMesh());

	AIControllerClass = AIGBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	BossDataAsset = FIGConstructorHelper::FindAndGetObject<UIGBossDataAsset>(TEXT("/Script/Indigo.IGBossDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_BossData.DA_BossData'"));
	GimmickDataAsset = FIGConstructorHelper::FindAndGetObject<UIGBossGimmickDataAsset>(TEXT("/Script/Indigo.IGBossGimmickDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_BossGimmickData.DA_BossGimmickData'"));

	FIGConstructorHelper::FindClassAndInitialize<UIGIngameHUDWidget>(TEXT("/Game/_GorillaJiphyunjeon/UI/Game/WBP_BossHUD.WBP_BossHUD_C"), [&](TSubclassOf<UIGIngameHUDWidget> Class)
	{
		HudWidgetClass = Class;
	}, EAssertionLevel::Check);

	FIGConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Mesh/Boss_eye.Boss_eye'"), [&](UStaticMesh* MeshRef)
	{
		EyeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeMesh"));
		EyeMesh->SetStaticMesh(MeshRef);
		EyeMesh->SetWorldLocation(GetMesh()->GetSocketLocation(BOSS_LEFT_HAND));
		EyeMesh->SetupAttachment(GetMesh());
	}, EAssertionLevel::Check);

	bIsFirstAttack = false;
	bIsFirstRangeAttack = false;
	bIsFirstFloorAttack = false;
	bIsFirstDeadInteract = false;
}

void AIGBoss::BeginPlay()
{
	Super::BeginPlay();

	CurrentGimmick = EAttackPattern::None;
	PlayerActor = UGameplayStatics::GetPlayerPawn(GWorld, 0);

	AnimInstance = CastChecked<UIGBossAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetSpeed(0.f);
	AnimInstance->OnGenerateBossCloseAttack.AddUObject(this, &AIGBoss::GenerateCloseAttack);
	AnimInstance->OnGenerateBossFloorAttack.AddUObject(this, &AIGBoss::GenerateFloorAttack);
	AnimInstance->OnGenerateBossFarAttack.AddUObject(this, &AIGBoss::GenerateFarAttack);
	AnimInstance->OnFinishAttack.AddUObject(this, &AIGBoss::EndAttack);
	StoppingDistance = BossDataAsset->StoppingDistance;
	MaxHp = BossDataAsset->MaxHp;
	Hp = MaxHp;

	Normal_Phase1Probability = GimmickDataAsset->Normal_Phase1Probability;
	CloseAttack_Phase1Probability = GimmickDataAsset->CloseAttack_Phase1Probability;
	FarAttack_Phase1Probability = GimmickDataAsset->FarAttack_Phase1Probability;
	FloorAttack_Phase1Probability = GimmickDataAsset->Floor_Phase1Probability;
	Normal_Phase2Probability = GimmickDataAsset->NormalAttack_Phase2Probability;
	CloseAttack_Phase2Probability = GimmickDataAsset->CloseAttack_Phase2Probability;
	FarAttack_Phase2Probability = GimmickDataAsset->FarAttack_Phase2Probability;
	FloorAttack_Phase2Probability = GimmickDataAsset->FloorAttack_Phase2Probability;

	CloseAttack_SpikeNum = GimmickDataAsset->CloseAttack_SpikeNum;
	CloseAttack_HandRadius = GimmickDataAsset->CloseAttack_HandRadius;
	CloseAttack_Damage = GimmickDataAsset->CloseAttack_Damage;
	CloseAttack_SpikeTimeGap = GimmickDataAsset->CloseAttack_SpikeTimeGap;
	CloseAttack_SpikeDistanceGap = GimmickDataAsset->CloseAttack_SpikeDistanceGap;
	CloseAttack_SpikeDuration = GimmickDataAsset->CloseAttack_SpikeDuration;
	CloseAttack_SpikeDestroyDelay = GimmickDataAsset->CloseAttack_SpikeDestroyDelay;
	CloseAttack_SpikeGroundOffset = GimmickDataAsset->CloseAttack_SpikeGroundOffset;

	FarAttack_Damage = GimmickDataAsset->FarAttack_Damage;
	FarAttack_ProjectileSpeed = GimmickDataAsset->FarAttack_ProjectileSpeed;
	FarAttack_ProjectileDuration = GimmickDataAsset->FarAttack_ProjectileDuration;

	FloorAttack_Damage = GimmickDataAsset->FloorAttack_Damage;
	FloorAttack_ProjectileDistance = GimmickDataAsset->FloorAttack_ProjectileDistance;
	FloorAttack_ProjectileNum = GimmickDataAsset->FloorAttack_ProjectileNum;
	FloorAttack_ProjectileSpeed = GimmickDataAsset->FloorAttack_ProjectileSpeed;
}

void AIGBoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AnimInstance->SetSpeed(GetVelocity().Size2D());

	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_LEFT_HAND), 100.f, 16, FColor::Red, false, 0.f);
	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_RIGHT_HAND), 100.f, 16, FColor::Red, false, 0.f);

	InteractCollider->SetRelativeLocation(GetActorLocation());
	DrawDebugBox(GetWorld(), GetActorLocation(), InteractCollider->GetScaledBoxExtent(), FColor::Green, false, 1.f);
	EyeMesh->SetWorldLocation(GetMesh()->GetSocketLocation(BOSS_LEFT_EYE));
	EyeMesh->SetWorldRotation(GetMesh()->GetSocketRotation(BOSS_LEFT_EYE));
}

float AIGBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HudWidget)
	{
		HudWidget->UpdateHpGauge(Hp);
	}

	if (Hp <= 0 && !bIsDead)
	{
		AnimInstance->Die();
		AnimInstance->OnFinishDead.AddUObject(this, &AIGBoss::FadeOut);
		if (HudWidget)
		{
			HudWidget->UpdateHpGauge(0.f);
		}
		bIsDead = true;
		Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->GetShinmyophil()->BattleRemakeBossDie();
		return DamageAmount;
	}
	return DamageAmount;
}

void AIGBoss::FadeOut()
{
	//Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->PlayFadeOutSequence();
}

void AIGBoss::Interact()
{
	if (bIsDead && !bIsFirstDeadInteract)
	{
		Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->GetShinmyophil()->BattleRemakeInteractBossDeadBody();
		bIsFirstDeadInteract = true;
	}
}

EAttackPattern AIGBoss::GetRandomAttackPatternByProbability()
{
	// 백분율로 계산
	const uint32 RandNum = FMath::RandRange(1, 100);
	const bool IsPhase1 = Hp > MaxHp / 2;

	// 검출 순서: 일반 공격 - 근거리 - 원거리 - 장판
	const float Normal_Phase1Check = Normal_Phase1Probability;
	const float CloseAttack_Phase1Check = Normal_Phase1Check + CloseAttack_Phase1Probability;
	const float FarAttack_Phase1Check = CloseAttack_Phase1Check + FarAttack_Phase1Probability;
	const float FloorAttack_Phase1Check = FarAttack_Phase1Check + FloorAttack_Phase1Probability;

	const float Normal_Phase2Check = Normal_Phase2Probability;
	const float CloseAttack_Phase2Check = Normal_Phase2Check + CloseAttack_Phase2Probability;
	const float FarAttack_Phase2Check = CloseAttack_Phase2Check + FarAttack_Phase2Probability;
	const float FloorAttack_Phase2Check = FarAttack_Phase2Check + FloorAttack_Phase2Probability;

	if (IsPhase1)
	{
		if (RandNum <= Normal_Phase1Check)
		{
			return static_cast<bool>(FMath::RandRange(0, 1)) ? EAttackPattern::NormalWeak : EAttackPattern::NormalStrong;
		}
		if (RandNum <= CloseAttack_Phase1Check)
		{
			return EAttackPattern::Close;
		}
		if (RandNum <= FarAttack_Phase1Check)
		{
			return EAttackPattern::Far;
		}
		if (RandNum <= FloorAttack_Phase1Check)
		{
			return EAttackPattern::Floor;
		}
	}
	else
	{
		if (RandNum <= Normal_Phase2Check)
		{
			return static_cast<bool>(FMath::RandRange(0, 1)) ? EAttackPattern::NormalWeak : EAttackPattern::NormalStrong;
		}
		if (RandNum <= CloseAttack_Phase2Check)
		{
			return EAttackPattern::Close;
		}
		if (RandNum <= FarAttack_Phase2Check)
		{
			return EAttackPattern::Far;
		}
		if (RandNum <= FloorAttack_Phase2Check)
		{
			return EAttackPattern::Floor;
		}
	}

	return EAttackPattern::None;
}

void AIGBoss::EnableHUD()
{
	if (HudWidget)
	{
		return;
	}

	HudWidget = CreateWidget<UIGIngameHUDWidget>(GetWorld(), HudWidgetClass);
	if (HudWidget)
	{
		HudWidget->AddToViewport();
		HudWidget->InitHpGauge(MaxHp, Hp);
	}
}

void AIGBoss::DisableHUD()
{
	if (!HudWidget)
	{
		return;
	}

	HudWidget->RemoveFromParent();
	HudWidget = nullptr;
}

void AIGBoss::PerformNormalWeakAttack()
{
	CurrentGimmick = EAttackPattern::NormalWeak;
	AnimInstance->StartWeakNormalAttack();
	if (!bIsFirstAttack)
	{
		Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->GetShinmyophil()->BattleRemakeBossFirstAttack();
		bIsFirstAttack = true;
	}
}

void AIGBoss::PerformNormalStrongAttack()
{
	CurrentGimmick = EAttackPattern::NormalStrong;
	AnimInstance->StartStrongNormalAttack();
	if (!bIsFirstAttack)
	{
		Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->GetShinmyophil()->BattleRemakeBossFirstAttack();
		bIsFirstAttack = true;
	}
}

void AIGBoss::PerformCloseAttack()
{
	CurrentGimmick = EAttackPattern::Close;
	AnimInstance->StartCloseAttack();
	if (!bIsFirstAttack)
	{
		Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->GetShinmyophil()->BattleRemakeBossFirstAttack();
		bIsFirstAttack = true;
	}
}

void AIGBoss::PerformFloorAttack()
{
	CurrentGimmick = EAttackPattern::Floor;
	AnimInstance->StartFloorAttack();
}

void AIGBoss::PerformFarAttack()
{
	CurrentGimmick = EAttackPattern::Far;
	AnimInstance->StartFarAttack();
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

	// 산 생성 -> 보스 Front방향으로 변경!
	FVector TargetVector = GetActorForwardVector();
	TargetVector.Normalize();

	for (uint32 i = 0; i < CloseAttack_SpikeNum; i++)
	{
		constexpr float Height = 300.f;
		FVector GenerationLocation = GetActorLocation() + TargetVector * CloseAttack_SpikeDistanceGap * (i + 1);
		GenerationLocation.Z = -Height + CloseAttack_SpikeGroundOffset;
		AIGMountainSpike* SpawnedSpike = GWorld->SpawnActor<AIGMountainSpike>(GenerationLocation, FRotator::ZeroRotator);
		SpawnedSpike->Init(CloseAttack_Damage, 300.f, CloseAttack_SpikeTimeGap * i, CloseAttack_SpikeDuration, CloseAttack_SpikeDestroyDelay);
	}
}

void AIGBoss::GenerateFloorAttack()
{
	float Angle = 0.f;
	for (uint32 i = 0; i < FloorAttack_ProjectileNum; ++i)
	{
		AIGStraightProjectile* SpawnedProjectile = GWorld->SpawnActor<AIGBossFlooringProjectile>(GetActorLocation(), FRotator(0.f, Angle, 0.f));
		SpawnedProjectile->Init(FloorAttack_Damage, SpawnedProjectile->GetActorForwardVector(), FloorAttack_ProjectileDistance, FloorAttack_ProjectileSpeed, EProjectileSpawnType::SpawnedByEnemy);
		Angle += 360.f / FloorAttack_ProjectileNum;
	}
}

void AIGBoss::GenerateFarAttack()
{
	AIGFollowProjectile* SpawnedProjectile = GWorld->SpawnActor<AIGFollowProjectile>(GetMesh()->GetSocketLocation(TEXT("LeftHand")), FRotator::ZeroRotator);
	SpawnedProjectile->Init(FarAttack_Damage, PlayerActor, FarAttack_ProjectileSpeed, FarAttack_ProjectileDuration, EProjectileSpawnType::SpawnedByEnemy);
}

void AIGBoss::EndAttack()
{
	CurrentGimmick = EAttackPattern::None;
	OnFinishBossAttack.Broadcast();
}
