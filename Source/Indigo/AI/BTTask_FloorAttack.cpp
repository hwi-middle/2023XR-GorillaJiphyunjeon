// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_FloorAttack.h"

#include "AIController.h"
#include "Indigo/Character/IGBoss.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_FloorAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ControllingBoss = Cast<AIGBoss>(ControllingPawn);
	if (!ControllingBoss)
	{
		return EBTNodeResult::Failed;
	}

	if(Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->IsDead())
	{
		return EBTNodeResult::Aborted;
	}

	CheckEndDelegateHandle = ControllingBoss->OnFinishBossAttack.AddLambda(
		[&]()
		{
			DeleteLambda();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	ControllingBoss->PerformFloorAttack();
	return EBTNodeResult::InProgress;
}

void UBTTask_FloorAttack::DeleteLambda()
{
	Cast<AIGBoss>(ControllingBoss)->OnFinishBossAttack.Remove(CheckEndDelegateHandle);
}

