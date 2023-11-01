// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/AI/WIspAI/BTService_WispDetectPlayer.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Indigo/AI/IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Constant/IGCollisionChannels.h"
#include "Kismet/GameplayStatics.h"

UBTService_WispDetectPlayer::UBTService_WispDetectPlayer()
{
	NodeName = TEXT("Detect Player");
	Interval = 0.1f;
}

void UBTService_WispDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	const UWorld* World = ControllingPawn->GetWorld();
	ensure(ControllingPawn);
	ensure(World);

	AIGHintMonsterBase* Wisp = Cast<AIGHintMonsterBase>(ControllingPawn);
	if (Wisp == nullptr)
	{		
		return;
	}

	if(Wisp->IsDead() || Wisp->GetIsHit())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		return;
	}

	const FVector Origin = Wisp->GetActorLocation();
	const float DetectRadius = 500.0f;

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	TArray<AActor*> IgnoredWisps;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIGHintMonsterBase::StaticClass(), IgnoredWisps);

	for (AActor* Wisps : IgnoredWisps) {
		CollisionParams.AddIgnoredActor(Wisps);
	}
	
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
		const FVector WispToTarget = Player->GetActorLocation() - Wisp->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Player);
		const bool IsCloseEnough = WispToTarget.Length() <= Wisp->GetStoppingDistance();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, IsCloseEnough);

		DrawDebugSphere(World, Origin, DetectRadius, 16, FColor::Green, false, 0.f);
		if (!IsCloseEnough)
		{
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Green, false, 0.f);
		}
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_IS_CLOSE_ENOUGH, false);
	DrawDebugSphere(World, Wisp->GetActorLocation(), DetectRadius, 16, FColor::Red, false, 0.1f);
}