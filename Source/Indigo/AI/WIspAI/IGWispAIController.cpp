// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/AI/WIspAI/IGWispAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Indigo/AI/IGAI.h"

AIGWispAIController::AIGWispAIController()
{
	BBAsset = FIGConstructorHelper::FindAndGetObject<UBlackboardData>(TEXT("/Script/AIModule.BlackboardData'/Game/_GorillaJiphyunjeon/AI/Wisp/BB_Wisp.BB_Wisp'"), EAssertionLevel::Check);
	BTAsset =  FIGConstructorHelper::FindAndGetObject<UBehaviorTree>(TEXT("/Script/AIModule.BehaviorTree'/Game/_GorillaJiphyunjeon/AI/Wisp/BT_Wisp.BT_Wisp'"), EAssertionLevel::Check);
}

void AIGWispAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if(UseBlackboard(BBAsset, BlackboardPtr))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AIGWispAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	BTComponent->StopTree();
}

void AIGWispAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
