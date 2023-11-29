// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTast_WispAttack.generated.h"

/**
 * 
 */

class AIGHintMonsterBase;

UCLASS()
class INDIGO_API UBTTast_WispAttack : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UBTTast_WispAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<AIGHintMonsterBase> ControllingWisp;
	
	FDelegateHandle CheckEndDelegateHandle;
	
	UPROPERTY()
	uint8 bIsFinished : 1;

private:
	void SetFinished();
};
