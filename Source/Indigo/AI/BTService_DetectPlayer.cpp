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

	TArray<FOverlapResult> OverlapResults;
	const FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Origin,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (!bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, false);
		DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.f);
		return;
	}

	for (const auto& OverlapResult : OverlapResults)
	{
		if (AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(OverlapResult.GetActor()))
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
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, false);
	DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.1f);
}
