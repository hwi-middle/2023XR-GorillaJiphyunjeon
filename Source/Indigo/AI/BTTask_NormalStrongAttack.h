// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NormalStrongAttack.generated.h"

class AIGBoss;
/**
 * 
 */
UCLASS()
class INDIGO_API UBTTask_NormalStrongAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UBTTask_NormalStrongAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<AIGBoss> ControllingBoss;
	
	UPROPERTY()
	uint8 bIsFinished : 1;
	
private:
	void SetFinished();
};
