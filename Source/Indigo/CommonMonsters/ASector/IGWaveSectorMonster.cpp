// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveSectorMonster.h"

#include "Indigo/Util/IGConstructorHelper.h"

AIGWaveSectorMonster::AIGWaveSectorMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	
		FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_C.SM_Monster_C'"), [&](USkeletalMesh* MeshRef)
    {
    GetMesh()->SetSkeletalMesh(MeshRef);
    	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
    }, EAssertionLevel::Check);
    	
    	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
    	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_C/ABP_Wisp_C.ABP_Wisp_C_C"), EAssertionLevel::Check);
    	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);
}

void AIGWaveSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetCrystalType(ECrystal::Wave);
}

void AIGWaveSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
