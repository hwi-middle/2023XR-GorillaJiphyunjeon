// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_DetermineAttackPattern.h"
#include "AIController.h"
#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGBoss.h"

EBTNodeResult::Type UBTTask_DetermineAttackPattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIGBoss* Boss = Cast<AIGBoss>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKEY_ATTACK_PATTERN, Boss->GetRandomAttackPatternByProbability());
	return EBTNodeResult::Succeeded;
}
