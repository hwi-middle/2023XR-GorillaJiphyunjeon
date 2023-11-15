// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_NormalWeakAttack.h"

#include "AIController.h"
#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGBoss.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_NormalWeakAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsEnum(BBKEY_ATTACK_PATTERN) != EAttackPattern::NormalWeak)
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

	CheckEndDelegateHandle = ControllingBoss->OnFinishBossAttack.AddLambda(
		[&]()
		{
			DeleteLambda();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	ControllingBoss->PerformNormalWeakAttack();
	return EBTNodeResult::InProgress;
}

void UBTTask_NormalWeakAttack::DeleteLambda()
{
	Cast<AIGBoss>(ControllingBoss)->OnFinishBossAttack.Remove(CheckEndDelegateHandle);
}