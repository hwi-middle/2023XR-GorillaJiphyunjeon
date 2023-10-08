// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGDummyEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Indigo/AI/IGBossAIController.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGDummyEnemy::AIGDummyEnemy()
{
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Boss/Mesh/SK_Boss.SK_Boss'"),[&](USkeletalMesh* MeshRef)
	{
		GetMesh()->SetSkeletalMesh(MeshRef);
		GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	}, EAssertionLevel::Check);

	AIControllerClass = AIGBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}
