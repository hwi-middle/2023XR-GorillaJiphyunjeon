// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/AI/WIspAI/BTTask_WispBomb.h"
#include "AIController.h"
#include "Indigo/AI/IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_WispBomb::UBTTask_WispBomb()
{
	bNotifyTick = true;
	bIsFinished = false;
}

EBTNodeResult::Type UBTTask_WispBomb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if(Player->IsDead() || ControllingWisp->IsDead())
	{
		return EBTNodeResult::Aborted;
	}
	
	ControllingWisp->OnFinishWispAttack.AddUObject(this, &UBTTask_WispBomb::SetFinished);
	ControllingWisp->PerformBombAttack();	
	return EBTNodeResult::InProgress;	
}

void UBTTask_WispBomb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsFinished)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		bIsFinished = false;
	}
}

void UBTTask_WispBomb::SetFinished()
{
	bIsFinished = true;
}
