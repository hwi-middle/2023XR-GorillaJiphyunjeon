// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTService_DetectPlayer.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Indigo/Enemy/IGEnemyBase.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("Detect Player");
	Interval = 0.5f;
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	const FVector Origin = ControllingPawn->GetActorLocation();
	const UWorld* World = ControllingPawn->GetWorld();
	ensure(ControllingPawn);
	ensure(World);

	const AIGEnemyBase* EnemyPawn = Cast<AIGEnemyBase>(ControllingPawn);
	if (EnemyPawn == nullptr)
	{
		return;
	}

	const float DetectRadius = EnemyPawn->GetDetectRange();

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
		DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.f);
		return;
	}
	
	for (const auto& OverlapResult : OverlapResults)
	{
		if (AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(OverlapResult.GetActor()))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Player);
			DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Green, false, 0.f);

			DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Green, false, 0.f);
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Green, false, 0.f);
			return;
		}
	}

	DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Red, false, 0.f);
}
