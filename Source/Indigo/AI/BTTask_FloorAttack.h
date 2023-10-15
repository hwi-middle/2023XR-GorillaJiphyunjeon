// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FloorAttack.generated.h"

class AIGBoss;
/**
 * 
 */
UCLASS()
class INDIGO_API UBTTask_FloorAttack : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	TObjectPtr<AIGBoss> ControllingBoss;
	
	FDelegateHandle CheckEndDelegateHandle;
	
private:
	void DeleteLambda();
};
