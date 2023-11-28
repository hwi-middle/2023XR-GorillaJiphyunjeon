// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainSectorMonster.h"

#include "Indigo/Util/IGConstructorHelper.h"

AIGMountainSectorMonster::AIGMountainSectorMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_A.SM_Monster_A'"), [&](USkeletalMesh* MeshRef)
{
GetMesh()->SetSkeletalMesh(MeshRef);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}, EAssertionLevel::Check);
	
	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_A/ABP_Wisp.ABP_Wisp_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);
}

void AIGMountainSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetCrystalType(ECrystal::Mountain);	
	
}

void AIGMountainSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
