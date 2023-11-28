// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPineTreeSectorMonster.h"
#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

// Sets default values
AIGPineTreeSectorMonster::AIGPineTreeSectorMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FIGConstructorHelper::FindObjectAndInitialize<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Mesh/SM_Monster_A.SM_Monster_A'"), [&](USkeletalMesh* MeshRef)
{
GetMesh()->SetSkeletalMesh(MeshRef);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}, EAssertionLevel::Check);
	
	const TSubclassOf<UIGWispAnimInstance> WispAnimInstanceClass = FIGConstructorHelper::FindAndGetClass<UIGWispAnimInstance>(
	TEXT("/Game/_GorillaJiphyunjeon/SkeletalMesh/Character/Monster/Animation/Monster_A/ABP_Wisp.ABP_Wisp_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(WispAnimInstanceClass);

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_WispGreen.NS_WispGreen'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	NiagaraComp->SetupAttachment(GetMesh());
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

