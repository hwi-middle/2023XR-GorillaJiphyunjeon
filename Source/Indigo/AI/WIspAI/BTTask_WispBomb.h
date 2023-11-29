// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WispBomb.generated.h"

class AIGHintMonsterBase;
/**
 * 
 */
UCLASS()
class INDIGO_API UBTTask_WispBomb : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UBTTask_WispBomb();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<AIGHintMonsterBase> ControllingWisp;
	
	UPROPERTY()
	uint8 bIsFinished : 1;

private:
	void SetFinished();
	
};
