// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMountainSectorMonster.h"
#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGMountainSectorMonster::AIGMountainSectorMonster()
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

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_WispYellow.NS_WispYellow'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	NiagaraComp->SetupAttachment(GetMesh());
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
