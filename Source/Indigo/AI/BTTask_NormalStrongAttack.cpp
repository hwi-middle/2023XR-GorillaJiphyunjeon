// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_NormalStrongAttack.h"

#include "AIController.h"
#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGBoss.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalStrongAttack::UBTTask_NormalStrongAttack()
{
	bNotifyTick = true;
	bIsFinished = false;
}

EBTNodeResult::Type UBTTask_NormalStrongAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsEnum(BBKEY_ATTACK_PATTERN) != EAttackPattern::NormalStrong)
	{
		return EBTNodeResult::Failed;
	}

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

	if (Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0))->IsDead())
	{
		return EBTNodeResult::Aborted;
	}

	ControllingBoss->OnFinishBossAttack.AddUObject(this, &UBTTask_NormalStrongAttack::SetFinished);
	ControllingBoss->PerformNormalStrongAttack();
	return EBTNodeResult::InProgress;
}

void UBTTask_NormalStrongAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsFinished)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		bIsFinished = false;
	}
}

void UBTTask_NormalStrongAttack::SetFinished()
{
	bIsFinished = true;
}
