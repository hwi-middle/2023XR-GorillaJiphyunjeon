// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGBossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "IGAI.h"

AIGBossAIController::AIGBossAIController()
{
	BBAsset = FIGConstructorHelper::FindAndGetObject<UBlackboardData>(TEXT("/Script/AIModule.BlackboardData'/Game/_GorillaJiphyunjeon/AI/BB_Boss.BB_Boss'"), EAssertionLevel::Check);
	BTAsset =  FIGConstructorHelper::FindAndGetObject<UBehaviorTree>(TEXT("/Script/AIModule.BehaviorTree'/Game/_GorillaJiphyunjeon/AI/BT_Boss.BT_Boss'"), EAssertionLevel::Check);
}

void AIGBossAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if(UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_ORIGINPOS, GetPawn()->GetActorLocation());
		RunBehaviorTree(BTAsset);
	}
}

void AIGBossAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	BTComponent->StopTree();
}

void AIGBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
