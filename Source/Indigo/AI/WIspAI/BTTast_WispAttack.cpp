// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/AI/WIspAI/BTTast_WispAttack.h"
#include "AIController.h"
#include "Indigo/AI/IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTast_WispAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ControllingWisp = Cast<AIGHintMonsterBase>(ControllingPawn);
	if (!ControllingWisp)
	{
		return EBTNodeResult::Failed;
	}

	AIGPlayerCharacter* Player = Cast<AIGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GWorld, 0));
	if(Player->IsDead())
	{
		return EBTNodeResult::Aborted;
	}
	
	CheckEndDelegateHandle = ControllingWisp->OnFinishWispAttack.AddLambda(
		[&]()
		{
			DeleteLambda();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

		ControllingWisp->PerformCloseAttack();	
		return EBTNodeResult::InProgress;			
}

void UBTTast_WispAttack::DeleteLambda()
{
	Cast<AIGHintMonsterBase>(ControllingWisp)->OnFinishWispAttack.Remove(CheckEndDelegateHandle);
}
