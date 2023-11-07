// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBoss.h"

#include "IGPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/AI/IGBossAIController.h"
#include "Indigo/Animation/IGBossAnimInstance.h"
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

	CloseAttack_SpikeNum = GimmickDataAsset->CloseAttack_SpikeNum;
	CloseAttack_HandRadius = GimmickDataAsset->CloseAttack_HandRadius;
	CloseAttack_Damage = GimmickDataAsset->CloseAttack_Damage;
	CloseAttack_SpikeTimeGap = GimmickDataAsset->CloseAttack_SpikeTimeGap;
	CloseAttack_SpikeDistanceGap = GimmickDataAsset->CloseAttack_SpikeDistanceGap;
	CloseAttack_SpikeDuration = GimmickDataAsset->CloseAttack_SpikeDuration;
	CloseAttack_SpikeDestroyDelay = GimmickDataAsset->CloseAttack_SpikeDestroyDelay;
	CloseAttack_SpikeGroundOffset = GimmickDataAsset->CloseAttack_SpikeGroundOffset;

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
	HudWidget->UpdateHpGauge(Hp);

	if (Hp <= 0 && !bIsDead)
	{
		AnimInstance->Die();
		AnimInstance->OnFinishDead.AddUObject(this, &AIGBoss::FadeOut);
		HudWidget->UpdateHpGauge(0.f);
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
	const uint32 ProjectileCount = 30;
	float Angle = 0.f;
	for (uint32 i = 0; i < ProjectileCount; ++i)
	{
		AIGStraightProjectile* SpawnedProjectile = GWorld->SpawnActor<AIGStraightProjectile>(GetActorLocation(), FRotator(0.f, Angle, 0.f));
		SpawnedProjectile->Init(10.f, SpawnedProjectile->GetActorForwardVector(), 10000.f, 10.f, EProjectileSpawnType::SpawnedByEnemy);
		Angle += 360.f / ProjectileCount;
	}


	// AIGTreeTorus* SpawnedTorus = GWorld->SpawnActor<AIGTreeTorus>(GetActorLocation(), FRotator::ZeroRotator);
	// SpawnedTorus->Init(10.f, 3.f);
}

void AIGBoss::GenerateFarAttack()
{
	AIGFollowProjectile* SpawnedProjectile = GWorld->SpawnActor<AIGFollowProjectile>(GetMesh()->GetSocketLocation(TEXT("LeftHand")), FRotator::ZeroRotator);
	SpawnedProjectile->Init(10.f, PlayerActor, 10000.f, 6.f, 3.f, EProjectileSpawnType::SpawnedByEnemy);
}

void AIGBoss::EndAttack()
{
	CurrentGimmick = EAttackPattern::None;
	OnFinishBossAttack.Broadcast();
}
