// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGDummyEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/AI/IGBossAIController.h"
#include "Indigo/Animation/IGBossAnimInstance.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/Constant/IGBossSockets.h"

AIGDummyEnemy::AIGDummyEnemy()
{
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Mesh/SK_Boss.SK_Boss'"),[&](USkeletalMesh* MeshRef)
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
}

void AIGDummyEnemy::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = CastChecked<UIGBossAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetSpeed(0.f);

}

void AIGDummyEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AnimInstance->SetSpeed(GetVelocity().Size2D());

	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_LEFT_HAND), 50.f, 16, FColor::Red, false, 0.f);
	DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation(BOSS_RIGHT_HAND), 50.f, 16, FColor::Red, false, 0.f);
}
