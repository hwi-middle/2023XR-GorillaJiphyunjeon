// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "BTTask_DetermineAttackPattern.h"

#include "IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/Character/IGBoss.h"

EBTNodeResult::Type UBTTask_DetermineAttackPattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const uint32 RandNum = FMath::RandRange(1, 3);
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKEY_ATTACK_PATTERN, RandNum);
	return EBTNodeResult::Succeeded;
}
