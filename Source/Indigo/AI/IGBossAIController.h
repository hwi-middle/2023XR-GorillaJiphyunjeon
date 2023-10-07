// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IGBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API AIGBossAIController : public AAIController
{
	GENERATED_BODY()

public:
	AIGBossAIController();

	void RunAI();
	void StopAI();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> BTAsset;
};
