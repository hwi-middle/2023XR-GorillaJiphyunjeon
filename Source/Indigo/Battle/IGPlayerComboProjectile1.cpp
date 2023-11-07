// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerComboProjectile1.h"

#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGPlayerComboProjectile1::AIGPlayerComboProjectile1()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Main_Attack_ProjectileA.NS_Main_Attack_ProjectileA'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	RootComponent = NiagaraComp;
	SetActorRotation(FRotator(0.f, -90.f, 0.f));
}
