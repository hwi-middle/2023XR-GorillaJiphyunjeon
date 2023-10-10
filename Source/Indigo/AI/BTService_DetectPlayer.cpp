// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTService_DetectPlayer.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGBoss.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Constant/IGCollisionChannels.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("Detect Player");
	Interval = 0.1f;
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	const UWorld* World = ControllingPawn->GetWorld();
	ensure(ControllingPawn);
	ensure(World);

	const AIGBoss* Boss = Cast<AIGBoss>(ControllingPawn);
	if (Boss == nullptr)
	{
		return;
	}

	const FVector Origin = Boss->GetOrigin();
	const float DetectRadius = Boss->GetDetectRange();

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Boss);
	
	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		Origin,
		Origin,
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParams
	);

	if (!bHit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, false);
		DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.f);
		return;
	}

	if (AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(Result.GetActor()))
	{
		const FVector BossToTarget = Player->GetActorLocation() - Boss->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Player);
		const bool IsCloseEnough = BossToTarget.Length() <= Boss->GetStoppingDistance();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, IsCloseEnough);

		DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Green, false, 0.1f);
		if (!IsCloseEnough)
		{
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Green, false, 0.f);
		}
		return;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, false);
	DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.1f);
}
