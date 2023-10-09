// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_CloseAttack.h"

#include "AIController.h"
#include "Indigo/Character/IGBoss.h"

EBTNodeResult::Type UBTTask_CloseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIGBoss* AIPawn = Cast<AIGBoss>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// FOnFinishBossCloseAttackDelegate OnAttackFinished;
	// OnAttackFinished.AddLambda(
	// 	[&]()
	// 	{
	// 		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	// 	}
	// );

	AIPawn->OnFinishBossCloseAttack.AddLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	AIPawn->PerformCloseAttack();
	return EBTNodeResult::InProgress;
}

