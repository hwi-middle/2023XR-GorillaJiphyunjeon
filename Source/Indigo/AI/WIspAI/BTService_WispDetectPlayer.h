// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_WispDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UBTService_WispDetectPlayer : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_WispDetectPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
