// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGWaveSectorMonster.h"
#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGWaveSectorMonster::AIGWaveSectorMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	
		FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_B.SM_Monster_B'"), [&](USkeletalMesh* MeshRef)
    {
    GetMesh()->SetSkeletalMesh(MeshRef);
    	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
    }, EAssertionLevel::Check);
    	
    	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
    	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_B/ABP_Wisp_B.ABP_Wisp_B_C"), EAssertionLevel::Check);
    	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);

		NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
    	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
    		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_WispBlue.NS_WispBlue'"),
    		EAssertionLevel::Check);
    	NiagaraComp->SetAsset(NiagaraSystem);
    	NiagaraComp->SetupAttachment(GetMesh());
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
