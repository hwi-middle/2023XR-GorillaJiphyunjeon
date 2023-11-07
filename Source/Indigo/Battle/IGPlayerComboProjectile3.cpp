// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGPlayerComboProjectile3.h"

#include "NiagaraComponent.h"
#include "Indigo/Util/IGConstructorHelper.h"

AIGPlayerComboProjectile3::AIGPlayerComboProjectile3()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileVFX"));
	UNiagaraSystem* NiagaraSystem = FIGConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/_GorillaJiphyunjeon/Effect/NS_Main_Attack_ProjectileC.NS_Main_Attack_ProjectileC'"),
		EAssertionLevel::Check);
	NiagaraComp->SetAsset(NiagaraSystem);
	RootComponent = NiagaraComp;
	SetActorRotation(FRotator(0.f, -90.f, 0.f));
}
