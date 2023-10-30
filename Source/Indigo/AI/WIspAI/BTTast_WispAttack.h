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
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	TObjectPtr<AIGHintMonsterBase> ControllingWisp;
	
	FDelegateHandle CheckEndDelegateHandle;
	
private:
	void DeleteLambda();
};
