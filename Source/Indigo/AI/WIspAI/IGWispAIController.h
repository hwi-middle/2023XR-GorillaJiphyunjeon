// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IGWispAIController.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API AIGWispAIController : public AAIController
{
	GENERATED_BODY()

public:
	AIGWispAIController();

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
