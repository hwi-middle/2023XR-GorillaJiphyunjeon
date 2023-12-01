// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGProvisoOldTreePlace.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "Indigo/Inventory/IGPlayerInventory.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Kismet/GameplayStatics.h"


AIGProvisoOldTreePlace::AIGProvisoOldTreePlace()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIGProvisoOldTreePlace::BeginPlay()
{
	Super::BeginPlay();
}

void AIGProvisoOldTreePlace::EnterPhasePlace()
{
	Super::EnterPhasePlace();
	if(PlayerCharacter == nullptr)
	{
		return;
	}
	UIGGameInstance* GameInstance = Cast<UIGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(
		(GameInstance->PlayerInventory->GetMountainCrystalArray().Num() +
		GameInstance->PlayerInventory->GetTreeCrystalArray().Num() +
		GameInstance->PlayerInventory->GetWaveCrystalArray().Num())
		< 9
		&& bIsInCollision == false)
	{
		PlayerCharacter->GetShinmyophil()->ProvisoRemakeCantFindCrystalAndCloseToOldTree();
	}
}

void AIGProvisoOldTreePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
