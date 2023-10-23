// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DetermineAttackPattern.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UBTTask_DetermineAttackPattern : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
