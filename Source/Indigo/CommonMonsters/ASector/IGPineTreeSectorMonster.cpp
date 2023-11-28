// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPineTreeSectorMonster.h"

#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGPineTreeSectorMonster::AIGPineTreeSectorMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_B.SM_Monster_B'"), [&](USkeletalMesh* MeshRef)
{
GetMesh()->SetSkeletalMesh(MeshRef);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}, EAssertionLevel::Check);
	
	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_B/ABP_Wisp_B.ABP_Wisp_B_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);
}

// Called when the game starts or when spawned
void AIGPineTreeSectorMonster::BeginPlay()
{
	Super::BeginPlay();
	SetCrystalType(ECrystal::Tree);
}

// Called every frame
void AIGPineTreeSectorMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

