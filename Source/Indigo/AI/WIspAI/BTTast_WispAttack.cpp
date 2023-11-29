// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/AI/WIspAI/BTTast_WispAttack.h"
#include "AIController.h"
#include "Indigo/AI/IGAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Indigo/CommonMonsters/IGHintMonsterBase.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTast_WispAttack::UBTTast_WispAttack()
{
	bNotifyTick = true;
	bIsFinished = false;
}

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
	if(Player->IsDead() || ControllingWisp->IsDead())
	{
		return EBTNodeResult::Aborted;
	}
	
	ControllingWisp->OnFinishWispAttack.AddUObject(this, &UBTTast_WispAttack::SetFinished);
	ControllingWisp->PerformCloseAttack();	
	return EBTNodeResult::InProgress;			
}

void UBTTast_WispAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsFinished)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		bIsFinished = false;
	}
}

void UBTTast_WispAttack::SetFinished()
{
	bIsFinished = true;
}
